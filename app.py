import os

# Import all the SQL stuff from the cs50 library
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configures Jinja with a custom filter
# usd will make it easier to format values as US dollars
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database, finance.db
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    stocks_owned = db.execute("SELECT stocks.symbol, shareholders.shares_owned FROM shareholders JOIN stocks ON shareholders.stock_id = stocks.id JOIN users ON users.id = shareholders.user_id WHERE users.id = ?", session["user_id"])

    # Create a list of unique stocks to not repeat
    unique_stocks = []
    index_display = []

    # Collect info regarding the stock symbol and amount of shares from the shareholders table
    for i in reversed(range(len(stocks_owned))):
        if not stocks_owned[i]["symbol"] in unique_stocks:
            unique_stocks.append(stocks_owned[i]["symbol"])
            stock_stats = lookup(stocks_owned[i]["symbol"])
            total_price = stock_stats["price"] * stocks_owned[i]["shares_owned"]
            if stocks_owned[i]["shares_owned"] != 0:
                index_display.append({"Name":stock_stats["name"], "Symbol":stocks_owned[i]["symbol"], "Price_per_Share":stock_stats["price"], "Number_of_Shares":stocks_owned[i]["shares_owned"], "Total_Price":total_price})

    # Collect Total Total Stock Price
    user_stock_cash = 0
    for i in range(len(index_display)):
        user_stock_cash += index_display[i]["Total_Price"]

    # Collect Residual information
    user_info = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    total_value = user_info[0]["cash"] + user_stock_cash

    return render_template("index.html", username=user_info[0]["username"], index_display=index_display, user_cash=user_info[0]["cash"], total_value=total_value, user_stock_cash=user_stock_cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        # Ensure user specified a symbol
        if not request.form.get("symbol"):
            return apology("must specify stock to buy")

        # Ensure the symbol is legit
        stock_stats = lookup(request.form.get("symbol"))
        if stock_stats == None:
            return apology("symbol does not exist")

        # Ensure user specified a number of shares
        elif not request.form.get("shares"):
            return apology("must specify number of shares")

        # Ensure that the number of shares is a positive integer
        while True:
            try:
                val = int(request.form.get("shares"))
                if val <= 0:
                    return apology("must specify a positive number of shares")
                break
            except ValueError:
                return apology("must specify a positive integer of shares")

        # Rename variables for ease of access
        symbol = stock_stats["symbol"]
        price_per_share = stock_stats["price"]
        number_of_shares = float(request.form.get("shares"))
        now = datetime.now()

        # Calculate total price and see if the user can purchase the shares of stock
        total_price = price_per_share * number_of_shares
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        if total_price > cash[0]["cash"]:
            return apology("not enough money!", 403)

        # If this stock has never been purchased before, add it to the stocks table
        symbols = db.execute("SELECT symbol FROM stocks")
        symbol_present = 0
        for i in range(len(symbols)):
            if symbols[i]["symbol"] == symbol:
                symbol_present = 1
        if symbol_present == 0:
            db.execute("INSERT INTO stocks (symbol) VALUES (?)", symbol)

        stock_id = db.execute("SELECT id FROM stocks WHERE symbol = ?", symbol)

        # Check whether user has bought this stock before, and change amount of stocks owned accordingly
        list_shares_owned = db.execute("SELECT shares_owned FROM shareholders WHERE user_id = ? AND stock_id = ?", session["user_id"], stock_id[0]["id"])
        shares_owned = 0
        if len(list_shares_owned) == 0:
            shares_owned = number_of_shares
        else:
            shares_owned = list_shares_owned[-1]["shares_owned"] + number_of_shares

        # Insert into the shareholders table the relevant information for this transaction
        db.execute("INSERT INTO shareholders (stock_id, user_id, shares, type, date, shares_owned, price_per_share) VALUES (?, ?, ?, ?, ?, ?, ?)", stock_id[0]["id"], session["user_id"], number_of_shares, "BUY", now, shares_owned, price_per_share)

        # Calculate and update cash balance
        cash = cash[0]["cash"] - total_price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])

        return redirect("/")

    else:
        return render_template("buy.html")

@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    """Allow Users to Change their Password"""

    if request.method == "POST":

        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        if not request.form.get("old_password"):
            return apology("must provide old password", 403)

        elif not request.form.get("new_password"):
            return apology("must provide new password", 403)

        elif not request.form.get("verify_new_password"):
            return apology("must verify new password", 403)

        elif request.form.get("new_password") != request.form.get("verify_new_password"):
            return apology("passwords do not match", 403)

        if not check_password_hash(rows[0]["hash"], request.form.get("old_password")):
            return apology("old password is incorrect", 403)

        new_password = generate_password_hash(request.form.get("new_password"))

        db.execute("UPDATE users SET hash = ? WHERE id = ?", new_password, session["user_id"])

        return redirect("/")

    else:
        return render_template("change_password.html")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT shareholders.type, stocks.symbol, shareholders.shares, shareholders.price_per_share, shareholders.date FROM shareholders JOIN stocks ON shareholders.stock_id = stocks.id JOIN users ON users.id = shareholders.user_id WHERE users.id = ?", session["user_id"])

    print(transactions)
    """history_display = []

    for i in (range(len(transactions))):
        history_display.append({"Type":transactions[i]["type"], "Symbol":transactions[i]["symbol"])"""

    user_info = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

    return render_template("history.html", username=user_info[0]["username"], transactions=transactions)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":

        symbol = request.form.get("symbol")

        if not request.form.get("symbol"):
            return apology("must provide symbol of stock")

        quote = lookup(symbol)

        if quote == None:
            return apology("symbol does not exist")

        return render_template("quoted.html", quote=quote)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    session.clear()

    # If the user submits a form, check for errors and register them
    if request.method == "POST":

        if not request.form.get("username"):
            return apology("must choose a username")

        elif not request.form.get("password"):
            return apology("must choose a password")

        elif not request.form.get("confirmation"):
            return apology("must verify your password")

        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match")

        usernames = db.execute("SELECT username FROM users")

        if any(d["username"] == request.form.get("username") for d in usernames):
            return apology("username taken", 403)

        username = request.form.get("username")
        password = generate_password_hash(request.form.get("password"))

        # Register the user
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, password)

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        session["user_id"] = rows[0]["id"]

        return(redirect("/"))

    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # Create a list of unique stocks that the user owns so it can be in the select menu
    stocks_owned = db.execute("SELECT stocks.symbol, shareholders.shares_owned FROM shareholders JOIN stocks ON shareholders.stock_id = stocks.id JOIN users ON users.id = shareholders.user_id WHERE users.id = ?", session["user_id"])
    unique_stocks = []
    do_not_add = []

    for i in reversed(range(len(stocks_owned))):
        if stocks_owned[i]["shares_owned"] == 0:
            do_not_add.append(stocks_owned[i]["symbol"])
        if not stocks_owned[i]["symbol"] in unique_stocks and not stocks_owned[i]["symbol"] in do_not_add:
            unique_stocks.append(stocks_owned[i]["symbol"])

    # If the user submits a form, check for errors then sell the stock
    if request.method == "POST":

        # Check for errors before selling the stock
        number_of_shares = float(request.form.get("shares"))
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must choose a symbol")

        elif not number_of_shares:
            return apology("must specify number of shares")

        while True:
            try:
                val = int(number_of_shares)
                if val <= 0:
                    return apology("must specify a positive number of shares")
                break
            except ValueError:
                return apology("must specify a positive integer of shares")

        shares_owned = db.execute("SELECT shareholders.shares_owned FROM shareholders JOIN stocks ON shareholders.stock_id = stocks.id WHERE symbol = ?", request.form.get("symbol"))
        if int(request.form.get("shares")) > shares_owned[-1]["shares_owned"]:
            return apology("you can't sell that many shares!", 403)

        # Get the stock stats
        stock_id = db.execute("SELECT id FROM stocks WHERE symbol = ?", symbol)
        stock_stats = lookup(request.form.get("symbol"))
        price_per_share = stock_stats["price"]
        total_price = price_per_share * number_of_shares
        now = datetime.now()

        list_shares_owned = db.execute("SELECT shares_owned FROM shareholders WHERE user_id = ? AND stock_id = ?", session["user_id"], stock_id[0]["id"])
        shares_owned = list_shares_owned[-1]["shares_owned"] - number_of_shares

        # Sell the stock
        db.execute("INSERT INTO shareholders (stock_id, user_id, shares, type, date, shares_owned, price_per_share) VALUES (?, ?, ?, ?, ?, ?, ?)", stock_id[0]["id"], session["user_id"], number_of_shares, "SELL", now, shares_owned, price_per_share)

        # Update the user's cash
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = cash[0]["cash"] + total_price
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])

        return(redirect("/"))

    else:
        return render_template("sell.html", unique_stocks=unique_stocks)
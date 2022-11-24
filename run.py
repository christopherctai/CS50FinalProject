from app import create_app

app = create_app()

if __name__ == '__main__':
    app.run(debug=True)

"""
@app.route("/login", methods=["GET", "POST"])
def login():
    # Log User In

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
    # Log User Out

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")

@app.route("/register", methods=["GET", "POST"])
def register():
    # Register User

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
            return apology("username taken")

        username = request.form.get("username")
        password = generate_password_hash(request.form.get("password"))

        # Register the user
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, password)

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("register.html")
"""
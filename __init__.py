import os
# Import all the SQL stuff from the cs50 library
from cs50 import SQL
from flask import Flask
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime
from flask_sqlalchemy import SQLAlchemy 
from flask_bcrypt import Bcrypt
from flask_login import LoginManager
from flask_mail import Mail, Message
from app.config import Config 



#session = Session()

# Configure CS50 Library to use SQLite database, finance.db
# db = SQL("sqlite:///icf.db")

# Configure the SQLAlchemy databse instead of using the CS50 one 
db = SQLAlchemy() 

# Initialize the bcrypt for use in the application  
bcrypt = Bcrypt()

# Initialize the login manager in the application. Handles sessions in the background for us 
login_manager = LoginManager()
# The view you pass in is the function name of the route, same as url_for function 
login_manager.login_view = 'users.login'
login_manager.login_message_category = 'info' 

mail = Mail()


# Trying something new with Amazon SES. Importing a Secret Key Here 
#Access Key ID: AKIAYS76MXFGMWNPAKV5
#Secret Access Key: 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




# Create a function so you can run the app w different configurations
def create_app(config_class=Config):
    # Configure application
    app = Flask(__name__)

    app.config.from_object(Config)

    db.init_app(app) 
    bcrypt.init_app(app)
    login_manager.init_app(app)
    mail.init_app(app)
    #Session.init_app(app)

    # The extension object not initially bound; no application specific state is stored on the extension object, so one extension object 
    from app.users.routes import users 
    from app.posts.routes import posts
    from app.main.routes import main
    from app.errors.handlers import errors
    app.register_blueprint(users)
    app.register_blueprint(posts)
    app.register_blueprint(main)
    app.register_blueprint(errors)

    return app
    

#current_app.app_context().push()

# Create different classes. can represent the database structure using classes/models 
# each class is a different table in the database 


#Then we create the database with the command line

"""
@current_app.after_request
def after_request(response):
    Ensure responses aren't cached
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

"""

"""

Notes from Corey 

USER AUTHENTICATION 

in the python3 runner, you can generate passwords like this 

This will create an instance 
bcrypt = Bcrypt()

This will produce a password hash 
bcrypt.generate_password_hash('testing')

This will produce a password hash in the form of a string 
bcrypt.generate_password_hash('testing').decode('utf-8')

These create different hashes every time! 

How can we verify if the user gets the right password? Use another method called check_password_hash!

This will check 'password' against the variable hashed_pw. It will return false, since we used 'testing' as our password
bcrypt.check_password_hash(hashed_pw, 'password')

"""

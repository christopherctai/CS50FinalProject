
# Used to have to do app.config['WHATEVER'] = 
# This makes them into actual variables 
# We also want to move these to environment variables 

import os

class Config:
    # Ensure templates are auto-reloaded
    TEMPLATES_AUTO_RELOAD = True

    # Configure session to use filesystem (instead of signed cookies)
    SESSION_PERMANENT = False
    SESSION_TYPE = "filesystem"
    # Set a secret key to prevent stuff from messing with session
    #imported secrets, then used secrets.token_hex(16)
    SECRET_KEY = os.environ.get('SECRET_KEY')
    # configure a SQL database. We can specify a sql path with /// in the URI. 
    SQLALCHEMY_DATABASE_URI = os.environ.get('SQLALCHEMY_DATABASE_URI')
    
    #SECRET_KEY = '85ec7591f12e263a857c091565e5f4d4'
    #SQLALCHEMY_DATABASE_URI = 'sqlite:///site.db'

    MAIL_SERVER = 'smpt.googlemail.com'
    MAIL_PORT = 587
    MAIL_USE_TLS = True
    MAIL_USE_SSL = False 
    MAIL_USERNAME = os.environ.get('MAIL_USERNAME')
    MAIL_PASSWORD = os.environ.get('MAIL_PASSWORD')


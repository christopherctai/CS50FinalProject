from app import db, login_manager
from flask import current_app 
from datetime import datetime
from flask_login import UserMixin
from itsdangerous import TimedJSONWebSignatureSerializer as Serializer

# To reload the user! Need to put in place for the extension to work, finding a user by ID 
# Make a decorated function 

# extension expects user model to have certain attributes or models. 
# Needs: IsAuthenticated, IsActive, IsAnonymous, and method called GetId. 
# This is so common that the extension provides a class to inherit from 
@login_manager.user_loader
def load_user(user_id):
    return User.query.get(int(user_id))

class User(db.Model, UserMixin):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(20), unique=True, nullable=False)
    email = db.Column(db.String(120), unique=True, nullable=False)
    image_file = db.Column(db.String(20), nullable=False, default='default.jpg')
    password = db.Column(db.String(60), nullable=False)
    # Says the post attribute has a relationship to the post model. 
    # We just get the user who made the post using the backref author thing 
    # lazy argument just says - SQL Alchemy will load the data as necessary in one go. Use post attribute to get ALL of the posts from one user
    # relationship, and NOT a column. We wouldn't see this post column here, it's just running an additional query in the background 
    posts = db.relationship('Post', backref='author', lazy=True)

    def get_reset_token(self, expires_sec=1800):
        s = Serializer(current_app.config['SECRET_KEY'], expires_sec)
        return s.dumps({'user_id': self.id}).decode('utf-8')

    @staticmethod
    def verify_reset_token(token):
        s = Serializer(current_app.config['SECRET_KEY'])
        try:
            user_id = s.loads(token)['user_id']
        except:
            return None
        return User.query.get(user_id)


    # Specify a magic method - how the method is printed when printed out
    def __repr__(self):
        return f"User('{self.username}', '{self.email}', '{self.image_file}')"

class Post(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    title = db.Column(db.String(100), nullable=False)
    date_posted = db.Column(db.DateTime, nullable=False, default=datetime.utcnow)
    content = db.Column(db.Text, nullable=False)
    # Here . in the foreign key it's the table name and column name 
    user_id = db.Column(db.Integer, db.ForeignKey('user.id'), nullable=False)
    # Going to make a one-to-many relationship between one user to all of their posts 

    def __repr__(self):
        return f"Post('{self.title}', '{self.date_posted}')"






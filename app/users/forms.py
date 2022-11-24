# users/forms.py
from flask_wtf import FlaskForm
from flask_wtf.file import FileField, FileAllowed
from wtforms import StringField, PasswordField, SubmitField, BooleanField
from wtforms.validators import DataRequired, InputRequired, Length, Email, EqualTo, ValidationError
from flask_login import current_user 
from app.models import User

class RegistrationForm(FlaskForm):
    # using the wtf forms package. I want a username field. Use StringField from the wtforms module
    # use VALIDATORS. We want user verification. Make sure there's a submission, and only a certain number of characters
    username = StringField('Username', validators=[InputRequired(), Length(min=2, max=20)])
    email = StringField('Email', validators=[InputRequired(), Email()])
    password = PasswordField('Password', validators=[InputRequired()])
    confirm_password = PasswordField('Confirm Password', validators=[InputRequired(), EqualTo('password')])
    submit = SubmitField('Sign Up')

    # create a custom validation with a function in the form 
    # Below is a template for validation methods! We'll add in a conditional, where if it meets the condition we can have an error
    """def validate_field(self, field):
        if True:
            raise ValidationError('Validation Message')"""

    def validate_username(self, username):
        # If there is a username that already exists we'll get a value back
        user = User.query.filter_by(username=username.data).first()
        # If user is none, then it won't do anything 
        if user:
            raise ValidationError('Username taken')

    def validate_email(self, email):
        # If there is a username that already exists we'll get a value back
        user = User.query.filter_by(email=email.data).first()
        # If user is none, then it won't do anything 
        if user:
            raise ValidationError('Email taken')

# Make a login form
class LoginForm(FlaskForm):
    email = StringField('Email', validators=[InputRequired(), Email()])
    password = PasswordField('Password', validators=[InputRequired()])
    # allow the system to remember the user after a while
    remember = BooleanField('Remember Me')
    submit = SubmitField('Login')


class UpdateAccountForm(FlaskForm):
    # using the wtf forms package. I want a username field. Use StringField from the wtforms module
    # use VALIDATORS. We want user verification. Make sure there's a submission, and only a certain number of characters
    username = StringField('Update Username', validators=[InputRequired(), Length(min=2, max=20)])
    email = StringField('Update Email', validators=[InputRequired(), Email()])
    picture = FileField('Update Profile Picture', validators=[FileAllowed(['jpg', 'png'])])
    submit = SubmitField('Update Account')

    def validate_username(self, username):
        # If there is a username that already exists we'll get a value back
        if username.data != current_user.username:
            user = User.query.filter_by(username=username.data).first()
            # If user is none, then it won't do anything 
            if user:
                raise ValidationError('Username taken')

    def validate_email(self, email):
        # If there is a username that already exists we'll get a value back
        if email.data != current_user.email:
            user = User.query.filter_by(email=email.data).first()
            # If user is none, then it won't do anything 
            if user:
                raise ValidationError('Email taken')
                
class RequestResetForm(FlaskForm):
    email = StringField('Email', validators=[InputRequired(), Email()])
    submit = SubmitField('Request Password Reset')

    def validate_email(self, email):
        # If there is a username that already exists we'll get a value back
        user = User.query.filter_by(email=email.data).first()
        # If user is none, then it won't do anything 
        if user is None:
            raise ValidationError('There is no account with that email!')

class ResetPasswordForm(FlaskForm):
    password = PasswordField('New Password', validators=[InputRequired()])
    confirm_password = PasswordField('Confirm Password', validators=[InputRequired(), EqualTo('password')])
    submit = SubmitField('Reset Password')

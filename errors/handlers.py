from flask import Blueprint, render_template

errors = Blueprint('errors', __name__)

# we use app_errorhandler, we want this error handler to work across the entire application 
@errors.app_errorhandler(404)
def error_404(error):
    return render_template('errors/404.html'), 404 
    # The second value is returned that is the status code. Default is 200

@errors.app_errorhandler(403)
def error_403(error):
    return render_template('errors/403.html'), 403 

@errors.app_errorhandler(500)
def error_500(error):
    return render_template('errors/500.html'), 500  


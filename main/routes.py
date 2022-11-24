# main/routes.py
from flask import render_template, request, Blueprint
from app.models import Post 

main = Blueprint('main', __name__)

@main.route("/")
def index():
    """Show user homepage"""
    
    return render_template("index.html")

@main.route("/wwb")
def wwb():
    return render_template("wwb.html")

@main.route("/leadership")
def leadership():
    return render_template("leadership.html")

@main.route("/student_leadership")
def student_leadership():
    return render_template("student_leadership.html")

@main.route("/sundays")
def sundays():
    return render_template("sundays.html")

@main.route("/general_events")
def general_events():
    return render_template("general_events.html")

@main.route("/special_events")
def special_events():
    return render_template("special_events.html")

@main.route("/church_events")
def church_events():
    return render_template("church_events.html")

@main.route("/become_a_member")
def become_a_member():
    return render_template("become_a_member.html")

@main.route("/serve_nomember")
def serve_nomember():
    return render_template("serve_nomember.html")

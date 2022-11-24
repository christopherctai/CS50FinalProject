# posts/routes.py
from flask import (render_template, url_for, flash,
                    redirect, request, abort, Blueprint)
from flask_login import current_user, login_required
from app import db 
from app.models import Post
from app.posts.forms import PostForm 

posts = Blueprint('posts', __name__)

@posts.route("/post/new", methods=['GET', 'POST'])
@login_required 
def new_post():
    form = PostForm()
    if form.validate_on_submit():
        post = Post(title=form.title.data, content=form.content.data, author=current_user)
        db.session.add(post)
        db.session.commit()
        flash('Your post has been created!', 'success') 
        return redirect(url_for('posts.announcements'))
    return render_template('create_post.html', form=form, legend="New Post")

@posts.route("/announcements", methods=['GET', 'POST'])
@login_required
def announcements():
    page = request.args.get('page', 1, type=int)
    posts = Post.query.order_by(Post.date_posted.desc()).paginate(page=page, per_page=5)
    return render_template('announcements.html', posts=posts)

@posts.route("/post/<int:post_id>")
@login_required 
def announcement_post(post_id):
    post = Post.query.get_or_404(post_id)
    return render_template('announcement_post.html', post=post)

@posts.route("/post/<int:post_id>/update", methods=['GET', 'POST'])
@login_required
def update_post(post_id):
    post = Post.query.get_or_404(post_id)
    if post.author != current_user:
        # 403 is the http response for forbidden route 
        abort(403) 
    form = PostForm()
    if form.validate_on_submit():
        post.title = form.title.data
        post.content = form.content.data
        # No need for an add, because these are already in the database. we're just updating something in the db 
        db.session.commit()
        flash('Your post has been updated!', 'success')
        return redirect(url_for('posts.announcement_post', post_id=post.id))
    elif request.method == 'GET':
        form.title.data = post.title
        form.content.data = post.content
    return render_template('create_post.html', form=form, legend="Update Post")
    
@posts.route("/post/<int:post_id>/delete", methods=['POST'])
@login_required
def delete_post(post_id):
    post = Post.query.get_or_404(post_id)
    if post.author != current_user:
        # 403 is the http response for forbidden route 
        abort(403) 
    db.session.delete(post)
    db.session.commit()
    flash('Your post has been deleted!', 'success')
    return redirect(url_for('posts.announcements'))

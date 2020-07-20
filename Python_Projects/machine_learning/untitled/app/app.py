from flask import render_template
from app import create_app
from app.files.users import user_api
from app.files.mails import mail_api
from app.files.folders import folder_api


app = create_app()
app.register_blueprint(user_api)
app.register_blueprint(mail_api)
app.register_blueprint(folder_api)


@app.route('/')
def hello_world():
    return render_template('index.html')


if __name__ == '__main__':
    app.run()

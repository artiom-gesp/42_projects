from flask import Flask, request, render_template
from flaskext.mysql import MySQL
from flask_bcrypt import Bcrypt
from pymysql import MySQLError
import json
from app.files.test import test_api

app = Flask(__name__)
app.register_blueprint(test_api)

mysql = MySQL()
bcrypt = Bcrypt(app)

app.config['MYSQL_DATABASE_HOST'] = 'localhost'
app.config['MYSQL_DATABASE_USER'] = 'root'
app.config['MYSQL_DATABASE_PASSWORD'] = 'testtest'
app.config['MYSQL_DATABASE_DB'] = 'mail'

mysql.init_app(app)
connection = mysql.connect()
cursor = connection.cursor()


@app.route('/')
def hello_world():
    return render_template('index.html')


@app.route('/users', methods=['GET'])
def get_user_list():
    if request.method == "GET":
        cursor.execute("SELECT `name` FROM `mailuser`")
        users = cursor.fetchall()
        cursor.close()
        return json.dumps(users)


@app.route('/users/<user_id>', methods=['GET'])
def get_user_by_id(user_id):
    if request.method == "GET":
        cursor.execute("SELECT `name` FROM `mailuser` WHERE id = %s", user_id)
        users = cursor.fetchall()
        cursor.close()
        return json.dumps(users)


@app.route('/users', methods=['POST'])
def create_user():
    if request.method == 'POST' and 'username' in request.form and 'password' in request.form \
            and 'mail' in request.form:
        name = request.form['username']
        mail = request.form['mail']
        pw_hash = bcrypt.generate_password_hash(request.form['password'])
        try:
            cursor.execute("INSERT INTO `mailuser` (`name`, `hashedPassword`, `mailAddress`) VALUES (%s, %s, %s)",
                           (name, pw_hash, mail))
            connection.commit()
        except MySQLError:
            return "Error connecting to mysql database"
        return "Success"


@app.route('/users/<user_id>', methods=['DELETE'])
def delete_user(user_id):
    if request.method == 'DELETE' and 'password' in request.form:
        try:
            cursor.execute("SELECT `hashedPassword` FROM `mailuser` WHERE id = %s", user_id)
            pw_hash = cursor.fetchone()
            if pw_hash and bcrypt.check_password_hash(pw_hash[0], request.form['password']):
                cursor.execute("DELETE FROM `mailuser` WHERE id = %s", user_id)
                connection.commit()
                return "Success"
        except MySQLError:
            return "Error connecting to mysql database"
        except ValueError:
            return "Wrong password"
    return "Could not delete user"


@app.route('/users/<user_id>', methods=['PUT'])
def update_user(user_id):
    if request.method == 'PUT' and 'password' in request.form:
        try:
            cursor.execute("SELECT `hashedPassword`, `name`, `mailAddress` FROM `mailuser` WHERE id = %s", user_id)
            response = cursor.fetchall()
            name_update = request.form['username'] if 'username' in request.form and request.form['username'] \
                else response[0][1]
            mail_update = request.form['mail'] if 'mail' in request.form and request.form['mail'] else response[0][2]
            print(response[0][0])
            print(response[0])
            if response and bcrypt.check_password_hash(response[0][0], request.form['password']):
                print('here update')
                cursor.execute("UPDATE `mailuser` SET `name` = %s, `mailAddress` = %s WHERE id = %s",
                               (name_update, mail_update, user_id))
                connection.commit()
                return "Success"
        except MySQLError:
            return "Error connecting to mysql database"
        except ValueError:
            return "Wrong password"
    return "Could not update user"


if __name__ == '__main__':
    app.run()

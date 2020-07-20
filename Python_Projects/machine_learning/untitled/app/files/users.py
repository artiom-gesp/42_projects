from flask import request
from flask import Blueprint
from flask_bcrypt import Bcrypt
from pymysql import MySQLError
from app import mysql
import json

"""Simple flask API to manipulate mailusers table in Mysql Database

    mailuser table features :
        ID
        mailAddress
        name
        hashedPassword
"""

user_api = Blueprint('user_api', __name__)
bcrypt = Bcrypt()


@user_api.route('/users', methods=['GET'])
def get_user_list():
    """Get list of all users in user table

        Returns:
            JSON: list of all users in JSON format
    """
    connection = mysql.connect()
    cursor = connection.cursor()
    if request.method == "GET":
        cursor.execute("SELECT `name`, `mailAddress` FROM `mailuser`")
        users = cursor.fetchall()
        cursor.close()
        return json.dumps(users)


@user_api.route('/users/<user_id>', methods=['GET'])
def get_user_by_id(user_id):
    """Get user by ID from user table

            Returns:
                JSON: user's name and email address in JSON format
    """
    connection = mysql.connect()
    cursor = connection.cursor()
    if request.method == "GET":
        cursor.execute("SELECT `name`, `mailAddress` FROM `mailuser` WHERE id = %s", user_id)
        users = cursor.fetchall()
        cursor.close()
        return json.dumps(users)


@user_api.route('/users', methods=['POST'])
def create_user():
    """Append new user to user table

            Returns:
                String: Success if operation successful else Error
    """
    if request.method == 'POST' and 'username' in request.form and 'password' in request.form \
            and 'mail' in request.form:

        name = request.form['username']
        mail = request.form['mail']
        password = request.form['password']

        if not password or not name or not mail:
            return "password, username and email fields cannot be empty"

        connection = mysql.connect()
        cursor = connection.cursor()

        pw_hash = bcrypt.generate_password_hash(password)
        try:
            cursor.execute("INSERT INTO `mailuser` (`name`, `hashedPassword`, `mailAddress`) VALUES (%s, %s, %s)",
                           (name, pw_hash, mail))
            connection.commit()
        except MySQLError:
            return "Error connecting to mysql database"
        return "Success"
    return "Error"


@user_api.route('/users/<user_id>', methods=['DELETE'])
def delete_user(user_id):
    """Delete user from user table

            Returns:
                String: Success if operation successful else Error
    """
    if request.method == 'DELETE' and 'password' in request.form:
        connection = mysql.connect()
        cursor = connection.cursor()
        try:
            cursor.execute("SELECT `hashedPassword` FROM `mailuser` WHERE id = %s", user_id)
            pw_hash = cursor.fetchone()

            #: if provided password is correct, delete user
            if pw_hash and bcrypt.check_password_hash(pw_hash[0], request.form['password']):
                cursor.execute("DELETE FROM `mailuser` WHERE id = %s", user_id)
                connection.commit()
                cursor.close()
                connection.close()
                return "Success"
        except MySQLError:
            cursor.close()
            connection.close()
            return "Error connecting to mysql database"
        except ValueError:
            cursor.close()
            connection.close()
            return "Wrong password"

    return "Could not delete user"


@user_api.route('/users/<user_id>', methods=['PUT'])
def update_user(user_id):
    """Update email from user table

            Returns:
                String: Success if operation successful else Error
    """
    if request.method == 'PUT' and 'password' in request.form:
        connection = mysql.connect()
        cursor = connection.cursor()
        try:
            cursor.execute("SELECT `hashedPassword` FROM `mailuser` WHERE id = %s", user_id)
            response = cursor.fetchone()

            name_update = request.form['username']
            mail_update = request.form['mail']

            #: if provided password is correct, update user's credentials
            if response and bcrypt.check_password_hash(response[0], request.form['password']):
                cursor.execute("UPDATE `mailuser` SET `name` = COALESCE(NULLIF(%s, ''), `name`), "
                               "`mailAddress` = COALESCE(NULLIF(%s, ''), `mailAddress`) WHERE id = %s",
                               (name_update, mail_update, user_id))
                connection.commit()
                cursor.close()
                connection.close()
                return "Success"
        except MySQLError:
            cursor.close()
            connection.close()
            return "Error connecting to mysql database"
        except ValueError:
            cursor.close()
            connection.close()
            return "Wrong password"
    return "Could not update user"

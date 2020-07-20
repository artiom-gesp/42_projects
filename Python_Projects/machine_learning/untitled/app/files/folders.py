from flask import request
from flask import Blueprint
from pymysql import MySQLError
from app import mysql
import json

"""Simple flask API to manipulate folder table in Mysql Database

    Folder table features :
        ID
        parentID
        name
        MailUser_ID
"""

folder_api = Blueprint('folder_api', __name__)


def get_folder_form_data(form):
    """Parse http request

        Returns:
            String : data send via http request as string
    """
    parent_id = form['parentID']
    name = form['name']
    user_id = form['MailUser_ID']

    return parent_id, name, user_id


@folder_api.route('/folders', methods=['GET'])
def get_folder_list():
    """Get a list of all folders from folder table

        Returns:
            JSON: folder in JSON format
    """
    if request.method == "GET":
        connection = mysql.connect()
        cursor = connection.cursor()
        try:
            cursor.execute("SELECT * FROM `folder`")
            folders = cursor.fetchall()
            cursor.close()
            connection.close()
            return json.dumps(folders)
        except MySQLError:
            cursor.close()
            connection.close()
            return "Error connecting to mysql"


@folder_api.route('/folders/<folder_id>', methods=['GET'])
def get_folder_by_id(folder_id):
    """Get single folder from folder table

        Returns:
            JSON: folder in JSON format
    """
    if request.method == "GET":
        connection = mysql.connect()
        cursor = connection.cursor()
        try:
            cursor.execute("SELECT * FROM `folder` WHERE id = %s", folder_id)
            folder = cursor.fetchall()
            return json.dumps(folder)
        except MySQLError:
            cursor.close()
            connection.close()
            return "Error connecting to mysql"


@folder_api.route('/folders', methods=['POST'])
def create_folder():
    """Append new folder to folder table

            Returns:
                String: Success if operation successful else Error
    """
    if request.method == 'POST' and 'parentID' in request.form and 'name' in request.form \
            and 'MailUser_ID' in request.form:

        parent_id, name, user_id = get_folder_form_data(request.form)

        if not parent_id or not name or not user_id:
            return "Missing data, could not create folder"

        connection = mysql.connect()
        cursor = connection.cursor()

        try:
            cursor.execute(
                "INSERT INTO `folder` (`parentID`, `name`, `MailUser_ID`) VALUES (%s, %s, %s)",
                (parent_id, name, user_id))
            connection.commit()
            cursor.close()
            connection.close()
            return "Success"
        except MySQLError:
            cursor.close()
            connection.close()
            return "Error connecting to mysql database"

    return "Error"


@folder_api.route('/folders/<folder_id>', methods=['DELETE'])
def delete_folder(folder_id):
    """Delete folder from folder table

            Returns:
                String: Success if operation successful else Error
    """
    if request.method == 'DELETE':
        connection = mysql.connect()
        cursor = connection.cursor()
        try:
            cursor.execute("DELETE FROM `folder` WHERE id = %s", folder_id)
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
    return "Could not delete folder"


@folder_api.route('/folders/<folder_id>', methods=['PUT'])
def update_folder(folder_id):
    """Update folder from folder table

            Returns:
                String: Success if operation successful else Error
    """
    if request.method == 'PUT':
        parent_id, name, user_id = get_folder_form_data(request.form)
        connection = mysql.connect()
        cursor = connection.cursor()
        try:
            cursor.execute(
                "UPDATE `folder` SET `parentID` = COALESCE(NULLIF(%s, ''), `parentID`),"
                "`name` = COALESCE(NULLIF(%s, ''), `name`), "
                "`MailUser_ID` = COALESCE(NULLIF(%s, ''), `MailUser_ID`)"
                "WHERE id = %s",
                (parent_id, name, user_id, folder_id))
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

    return "Could not update folder"

from flask import request
from flask import Blueprint
from pymysql import MySQLError
from app import mysql
import json


"""Simple flask API to manipulate mail table from Mysql Database

    mail table features :
        ID
        fromMail
        fromName
        receivedData
        subject
        body
        Folder_ID
        MailUser_ID
"""

mail_api = Blueprint('mail_api', __name__)


def get_mail_form_data(form):
    """Parse http request

        Args:
            Http request form

        Returns:
            String : data send via http request as string
    """
    from_mail = form['fromMail']
    from_name = form['fromName']
    received_data = form['receivedData']
    subject = form['subject']
    body = form['body']
    folder_id = form['Folder_ID']
    mail_user_id = form['MailUser_ID']

    return from_mail, from_name, received_data, subject, body, folder_id, mail_user_id


@mail_api.route('/mails', methods=['GET'])
def get_mail_list():
    """Get list of all emails in mail table

        Returns:
            JSON: list of emails in JSON format
    """
    if request.method == "GET":
        connection = mysql.connect()
        cursor = connection.cursor()
        try:
            cursor.execute("SELECT * FROM `mail`")
            mails = cursor.fetchall()
            cursor.close()
            connection.close()
            return json.dumps(mails)
        except MySQLError:
            cursor.close()
            connection.close()
            return "Error connecting to mysql"


@mail_api.route('/mails/<mail_id>', methods=['GET'])
def get_mail_by_id(mail_id):
    """Get single email by ID from mail table

            Returns:
                JSON: corresponding email in JSON format
    """
    if request.method == "GET":
        connection = mysql.connect()
        cursor = connection.cursor()
        try:
            cursor.execute("SELECT * FROM `mail` WHERE id = %s", mail_id)
            mail = cursor.fetchall()
            return json.dumps(mail)
        except MySQLError:
            cursor.close()
            connection.close()
            return "Error connecting to mysql"


@mail_api.route('/mails', methods=['POST'])
def create_mail():
    """Append new email to mail table

            Returns:
                String: Success if operation successful else Error
    """
    if request.method == 'POST' and 'fromMail' in request.form and 'fromName' in request.form \
            and 'receivedData' in request.form and 'subject' in request.form and 'Folder_ID' in request.form \
            and 'MailUser_ID' in request.form and 'body' in request.form:

        from_mail, from_name, received_data, subject, body, folder_id, mail_user_id = get_mail_form_data(request.form)
        if not from_name or not from_mail or not received_data or not subject or not body \
                or not folder_id or not mail_user_id:
            return "Missing data, could not append email to database"

        connection = mysql.connect()
        cursor = connection.cursor()

        try:
            cursor.execute(
                "INSERT INTO `mail` (fromMail, fromName, receivedData, subject, body, Folder_ID, MailUser_ID)"
                "VALUES (%s, %s, %s, %s, %s, %s, %s)",
                (from_mail, from_name, received_data, subject, body, folder_id, mail_user_id))
            connection.commit()
            cursor.close()
            connection.close()
            return "Success"
        except MySQLError:
            cursor.close()
            connection.close()
            return "Error connecting to mysql database"

    return "Error"


@mail_api.route('/mails/<mail_id>', methods=['DELETE'])
def delete_mail(mail_id):
    """Delete email from mail table

            Returns:
                String: Success if operation successful else Error
    """
    if request.method == 'DELETE':
        connection = mysql.connect()
        cursor = connection.cursor()
        try:
            cursor.execute("DELETE FROM `mail` WHERE id = %s", mail_id)
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
    return "Could not delete mail"


@mail_api.route('/mails/<mail_id>', methods=['PUT'])
def update_mail(mail_id):
    """Update email from mail table

            Returns:
                String: Success if operation successful else Error
    """
    if request.method == 'PUT':
        connection = mysql.connect()
        cursor = connection.cursor()
        try:
            from_mail, from_name, received_data, subject, body, folder_id, mail_user_id = \
                get_mail_form_data(request.form)

            cursor.execute(
                "UPDATE `mail` SET `fromMail` = COALESCE(NULLIF(%s, ''), `fromMail`),"
                "`fromName` = COALESCE(NULLIF(%s, ''), `fromName`), "
                "`receivedData` = COALESCE(NULLIF(%s, ''), `receivedData`), "
                "`subject` = COALESCE(NULLIF(%s, ''), `subject`),"
                "`body` = COALESCE(NULLIF(%s, ''), `body`),"
                "`Folder_ID` = COALESCE(NULLIF(%s, ''), `Folder_ID`),"
                "`MailUser_ID` = COALESCE(NULLIF(%s, ''), `MailUser_ID`)"
                "WHERE id = %s",
                (from_mail, from_name, received_data, subject, body, folder_id, mail_user_id, mail_id))
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

    return "Could not update mail"

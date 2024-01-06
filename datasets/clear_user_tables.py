import json
import mysql.connector


# Specify the path to your JSON file
config_path = "../config/config.json"

# Read the JSON file
with open(config_path, "r") as json_file:
    data = json.load(json_file)

# Create the config dictionary using values from the JSON data
config = {
    'user': data["DATABASE_USER"],
    'password': data["DATABASE_PASSWORD"],
    'host': data["DATABASE_URL"],
    'database': data["DATABASE_NAME"],
}

# Connect to MySQL database
conn = mysql.connector.connect(**config)

# Create a cursor object to execute SQL queries
cursor = conn.cursor()


cursor.execute('SET FOREIGN_KEY_CHECKS=0')

cursor.execute('DELETE FROM users')
cursor.execute('DELETE FROM user_degrees')
cursor.execute('DELETE FROM user_courses')
cursor.execute('DELETE FROM user_institution')

cursor.execute('SET FOREIGN_KEY_CHECKS=1')

# Commit changes and close the connection
conn.commit()
conn.close()
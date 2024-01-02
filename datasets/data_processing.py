import json
import mysql.connector

# Replace these values with your MySQL server details
config = {
    'user': 'lascelle',
    'password': 'password',
    'host': 'localhost',
    'database': 'lurm_db',
}

# Connect to MySQL database
conn = mysql.connector.connect(**config)

# Create a cursor object to execute SQL queries
cursor = conn.cursor()


cursor.execute('SET FOREIGN_KEY_CHECKS=0')

with open('institutions.json') as json_file:
    data = json.load(json_file)
    for university in data['universities']:
        print(university['name'])
        print(university['code'])
        cursor.execute('SELECT code FROM institutions WHERE code = %s', (university['code'],))
        existing_university = cursor.fetchone()
        if existing_university:
            print(f"University code {university['code']} already exists.")
        else:
            uni_query = 'INSERT INTO institutions(name,code) VALUES(%s,%s)'
            cursor.execute(uni_query,(university['name'],university['code']))
        for degree in university['degrees']:
            print(f"  {degree['name']}")
            print(f"  {degree['code']}")
            cursor.execute('SELECT code FROM degrees WHERE code = %s', (degree['code'],))
            existing_degree = cursor.fetchone()
            if existing_degree:
                print(f"Degree code {degree['code']} already exists.")
            else:
                degree_query = 'INSERT INTO degrees(name,code) VALUES(%s,%s)'
                cursor.execute(degree_query,(degree['name'],degree['code']))
            institutions_degree = 'INSERT INTO institutions_degree(degree_code, institution_code) VALUES(%s,%s)'
            cursor.execute(institutions_degree,(degree['code'],university['code']))
            for course in degree['courses']:
                print(f"    {course['code']} - {course['name']}")

                cursor.execute('SELECT code FROM course WHERE code = %s', (course['code'],))
                existing_course = cursor.fetchone()
                if existing_course:
                    print(f"Course code {course['code']} already exists.")
                else:
                    course_query = 'INSERT INTO course(name,code) VALUES(%s,%s)'
                    cursor.execute(course_query,(course['name'],course['code']))
                degree_courses = 'INSERT INTO degree_courses(course_code, degree_code) VALUES(%s,%s)'
                cursor.execute(degree_courses,(course['code'],degree['code']))




cursor.execute('SET FOREIGN_KEY_CHECKS=1')

# Commit changes and close the connection
conn.commit()
conn.close()
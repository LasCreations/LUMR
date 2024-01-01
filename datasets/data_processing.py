import json

with open('institutions.json') as json_file:
    data = json.load(json_file)
    for university in data['universities']:
        print(university['name'])
        for degree in university['degrees']:
            print(f"  {degree['name']}")
            for course in degree['courses']:
                print(f"    {course}")
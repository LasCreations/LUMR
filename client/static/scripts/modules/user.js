export default class User{
    constructor(firstname, lastname, username, password,  avatar, institutionName, rank, 
                degrees = [], courses = [], yearStart, yearEnd){
        this.firstname = firstname;
        this.lastname = lastname;
        this.username = username;
        this.password = password;
        this.avatar = avatar;
        this.rank = rank;
        this.institutionName = institutionName;
        this.degrees = degrees;
        this.courses = courses;
        this.yearStart = yearStart;
        this.yearEnd = yearEnd;
    }
}
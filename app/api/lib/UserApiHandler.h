#ifndef USER_API_HANDLER
#define USER_API_HANDLER

#ifdef __cplusplus
// C++ specific code goes here

#include "common.h"
#include "../../database/lib/DBConnector.h"
#include "../../database/models/user.h"

//Create a connection
DBConnector *dbConn = new DBConnector();

/*!
 * @function    parseHttpRequest
 * @abstract    Remove Json from body
 * @discussion  This function takes a request sent
 *              over http and removes the json value
 * @param       request    A char pointer value that stores the request
 * @result      Return a string value to be parsed into smaller tokens
*/
string parseHttpRequest(char *body);


/*!
 * @function    parseJSONTokens
 * @abstract    
 * @discussion  
 * @param       username
 * @param       email
 * @param       password
 * @param       jsonData
 * @result      null
*/
void parseJSONTokens(string &username, string &email, string &password, string &avatarurl, string JsonString);


/*!
 * @function    generateRandomCookieCode
 * @abstract    Generates an unique random cookie to be stored
 *              in the users browser
 * @discussion  This function takes a lenght in integer
 *              and generates a cookie string value
 * @param       length    an integer value that stores the length the
 *                          cookie should be.
 * @result      Return a string value.
*/
string generateRandomCookieCode(int length);


/*!
 * @function    addUserToDatabase
 * @abstract    Add user data to mysql database
 * @discussion  This function will be used to send the user data
 *              to the database 
 * @param       username    
 * @param       email    
 * @param       password
 * @param       cookie
 * @result      Return true if successfully added
*/
bool addUserToDatabase(string username, string email, string password, string avatarurl, string cookie);


/*!
 * @function    parseCookie
 * @abstract    
 * @discussion  
 * @param       request
 * @result      
*/
string parseCookie(char *request);


/*!
 * @function    getUserData
 * @abstract    
 * @discussion  
 * @param       username
 * @param       password
 * @result      
*/
User getUserData(string username, string password);


/*!
 * @function    getUserData
 * @abstract    
 * @discussion  
 * @param       cookie
 * @result      
*/
User *getUserData(string cookie);


/*!
 * @function    getUserData
 * @abstract    
 * @discussion  
 * @param       cookie
 * @result      
*/
string ParseUserDataToJSON(string username, string password, string email, string avatarurl);

#endif



#ifdef __cplusplus
extern "C" {
#endif
// C specific code goes here

#include <stdbool.h>

/*!
 * @function    handleUserRequests
 * @abstract    Accepts the user request 
 * @discussion  Sends to request to the correct functions
 * @param       request    A char pointer value that stores the request
 * @param       clientSocker    An integer value that stores socket the client is bind to
 * @result      null
*/
void handleUserRequests(char *request, char *method, const char *route, int clientSocket);


bool isAuth(char *request, char *method, const char *route, int clientSocket);

#ifdef __cplusplus
}
#endif



#endif
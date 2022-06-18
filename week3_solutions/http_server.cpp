#include "http_server.hh"

#include <vector>

#include <sys/stat.h>

#include <fstream>
#include <sstream>
#include <dirent.h>
#define BLOCKSIZE 100

using namespace std;

vector<string> split(const string &s, char delim) {
  vector<string> elems;

  stringstream ss(s);
  string item;

  while (getline(ss, item, delim)) {
    if (!item.empty())
      elems.push_back(item);
  }

  return elems;
}

HTTP_Request::HTTP_Request(string request) {
  vector<string> lines = split(request, '\n');
  vector<string> first_line = split(lines[0], ' ');

  this->HTTP_version = "1.0"; // We'll be using 1.0 irrespective of the request

  /*
   TODO : extract the request method and URL from first_line here
  */
  this->method = first_line[0];
  this->url = first_line[1];

  if (this->method != "GET") {
    cerr << "Method '" << this->method << "' not supported" << endl;
    exit(1);
  }
}

HTTP_Response *handle_request(string req) {
  HTTP_Request *request = new HTTP_Request(req);

  HTTP_Response *response = new HTTP_Response();

  string url = string("html_files") + request->url;

  response->HTTP_version = "HTTP/1.0";

  struct stat sb;
  if (stat(url.c_str(), &sb) == 0) // requested path exists
  {
    response->status_code = "200";
    response->status_text = "OK";
    response->content_type = "text/html";

    string body;

    if (S_ISDIR(sb.st_mode)) {
      /*
      In this case, requested path is a directory.
      TODO : find the index.html file in that directory (modify the url
      accordingly)
      */ 
      DIR *dir;
      struct dirent *ent;
      if ((dir = opendir (url.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
          printf ("%s\n", ent->d_name);
          if(ent->d_name == "index.html")
          {
            url = url + string("index.html");
          }
        }
        closedir (dir);
      }

    }

    /*
    TODO : open the file and read its contents
    */
       ifstream fin;
       string line;
       string responseBody;
       fin.open(url);
      
       while (fin) {
        // Read a Line from File
        getline(fin, line);
        responseBody = responseBody + line;
        // Print line in Console
        //cout << line << endl;
      }

    /*
    TODO : set the remaining fields of response appropriately
    */
       response->content_length =  responseBody.length();
       response->body = responseBody;
  }

  else {
    /*
    TODO : set the remaining fields of response appropriately
    */
    response->status_code = "404";
    response->status_text = "Page not found";
    response->content_type = "text/html";

    string responseBody ="Page Not Found :-)";
    response->content_length =  responseBody.length();
    response->body = responseBody;
  }

  delete request;

  return response;
}

string HTTP_Response::get_string() {
  /*
  TODO : implement this function
  */
  string responseString = this->HTTP_version + " " + 
                          this->status_code + " " + this->status_text + "\n" + this->content_type + "\n" + this->content_length +
                          + "\n" + this->body;
  return responseString;
}

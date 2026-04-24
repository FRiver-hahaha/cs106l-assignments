/*
 * CS106L Assignment 2: Marriage Pact
 * Created by Haven Whitney with modifications by Fabio Ibanez & Jacob Roberts-Baca.
 *
 * Welcome to Assignment 2 of CS106L! Please complete each STUDENT TODO
 * in this file. You do not need to modify any other files.
 *
 */

#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_set>
#include <sstream>
#include <random>

std::string kYourName = "Louis Armstrong"; // Don't forget to change this!

/**
 * Takes in a file name and returns a set containing all of the applicant names as a set.
 *
 * @param filename  The name of the file to read.
 *                  Each line of the file will be a single applicant's name.
 * @returns         A set of all applicant names read from the file.
 *
 * @remark Feel free to change the return type of this function (and the function
 * below it) to use a `std::unordered_set` instead. If you do so, make sure
 * to also change the corresponding functions in `utils.h`.
 */
std::set<std::string> get_applicants(std::string filename) {
  std::set<std::string> tempSet;
  std::ifstream infile(filename);
  std::string tempName;
  while(std::getline(infile, tempName)) {
    tempSet.insert(tempName);
  }
  infile.close();
  return tempSet;
}

std::string getTwoChar(const std::string& target) {
  std::stringstream ss(target);
  std::string firstName, lastName;
  ss >> firstName >> lastName;

  if(firstName.empty() || lastName.empty()) {
    return "";
  }

  return std::string(1, firstName[0]) + std::string(1, lastName[0]);
}

/**
 * Takes in a set of student names by reference and returns a queue of names
 * that match the given student name.
 *
 * @param name      The returned queue of names should have the same initials as this name.
 * @param students  The set of student names.
 * @return          A queue containing pointers to each matching name.
 */
std::queue<const std::string*> find_matches(std::string name, std::set<std::string>& students) {
  std::queue<const std::string*> tempQue;

  std::string targetName = getTwoChar(name);
  for(const auto& p : students) {
    if(getTwoChar(p) == targetName) {
      tempQue.push(&p);
    }
  }
  return tempQue;
}

/**
 * Takes in a queue of pointers to possible matches and determines the one true match!
 *
 * You can implement this function however you'd like, but try to do something a bit
 * more complicated than a simple `pop()`.
 *
 * @param matches The queue of possible matches.
 * @return        Your magical one true love.
 *                Will return "NO MATCHES FOUND." if `matches` is empty.
 */
std::string get_match(std::queue<const std::string*>& matches) {
  const std::string* result;
  if(!matches.empty()) {
     static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, matches.size() - 1);
    int randomIndex = dis(gen);

    for(int i = 0; i < randomIndex; ++i) {
      matches.push(matches.front());
      matches.pop();
    }

    result = matches.front();
    matches.pop();
  }else {
    std::cout << "“NO MATCHES FOUND.”" << std::endl;
    return "";
  }

  return *result;
}

/* #### Please don't remove this line! #### */
#include "autograder/utils.hpp"

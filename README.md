# Project Overview

## Getting started with a C++ Health Assistant Command Line Application integrated with Postgresql
# This repository contains a C++ console application that demonstrates Basic CRUD Operations on patient
# records, backed by a PostgreSQL database. The project uses  libpqxx for database connectivity and 
# nlohmann-json for handling structured data

# The Application functions as a simple health assistant application. It allows users to:
# 1: Add a new patient record with details on nutrition, fitness, mental status and skincare
# 2: Retrieve Patient Information by their ID
# 3: Update an Existing patient data
# 4: Delete an existing Patient Record
# 5: List all patients stored in the Database

# The Patient's health data(nutrition, fitness e.t.c) is stored in a structured JSON Format within a single JSONB column in the PostgreSQL  table, a modern approach for data modelling

# Prerequisites
# PostgreSQL : Must be installed and running in your system
# C++ compiler: A compiler that supports C++ 11 OR newer
# vcpkg: Recommended for easy package/library management

# Setup and Installation
# 1: Clone the Repository
#  git clone <repository_url>
# cd <repository_name>

# Install PostgreSQL on All Platforms
# Windows:  
  Download installer = Go to the official PostgreSQL download page and get the interactive installer by Enterprise DB. This is the simplest way to install PostgreSQL on windows
  
  Run the Installer
  - The installer will guide one through the process. Choose the components to be installed (PostgreSQL  Server, pgAdmin, Stack Builder)
  - Set a strong password for the postgres superuser
  - Specify the port number (default: 5432)
  - Wait for complete installation

  Start the server: The Installer typically sets up the PostgresSQL as a Window Service, so it will start automatically. You can manage it in the Service Control Panel

# Linux
   1) Update Package Lists:
   Debian/Ubuntu: sudo apt update
   RedHat/ Fedora: sudo dnf install postgresql-server

   2) Install PostgreSQL
   Debian/Ubuntu: sudo apt install postgresql postgresql-contrib
   RedHat/Fedora: sudo dnf install postgresql-server

   3) Initialize Database(if needed): On some distributions you may need to manually initialize the database cluster
   Debian/Ubuntu: No action needed, the package handles this
   RedHat/Fedora : sudo postgresql-setup --initdb

   4) Start and enable the service:
     sudo systemctl start postgresql
     sudo systemctl enable postgresql


# macOS   
    1) Homebrew(Recommended) : Install it from brew.sh
    2) Install PostgreSQL: brew install postgresql
    3) Start the Service: brew services start postgresql   


# Installing  C++ compilers and Visual Studio Code
1. Windows
 . Install MinGW-w64:
   Download the MinGW-w64 installer from the official site
   During installation, select x86_64 architecture
   Add the bin directory of MinGW-w64 installation to system's path environment variable

 . Visual Studio Code
   Download and install VSCode
   Go to the extension market place and install C/C++ extension from Microsoft
   Install the C++ intellisense extension for code completion and navigation

2. Linux
   Install g++
   Debian/Ubuntu sudo apt update && sudo apt install build-essential(This installs g++ and other tools)

  . Visual Studio Code
   Download the .deb or .rpm package from the VSCode website and install it
   Install the C/C++ and C++ intellisense extensions

 3. MacOS
    Install XCode Command Line Tool
    Open terminal and run xcode-select --install. This installs g++ and clang++
    compilers

    Visual Studio Code
    Download and install Visual Studio Code from the website
    Install the C/C++ and C++ intellisense extensions


# PostgreSQL Compatibility and C++ Compatibility
- The most popular library is libpqxx

Installing libpqxx: Use vcpkg
-------------------------------------------------------------------------------------------------------
Windows: 
# Install git(if not already installed) vcpkg is hosted in github, Git clone the repository
# git clone https://github.com/microsoft/vcpkg.git
# cd vcpkg

Run the Bootstrap Script to compile the vcpkg executable
# .\bootstrap-vcpkg.bat

Integrate with Visual Studio
# .\vcpkg integrate install

# Add vcpkg to SYSTEM Path
# Open System Properties -> Environment Variables
# Add the full path to the vcpkg folder

To install library client
# .\vcpkg install libpq:x64-windows - installs static/dynamic libraries and headers to connect with PostgreSQL from C/C++

Install the C++ wrapper(Optional using C++)
# .\vcpkg install libpqxx:x64-windows
-------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------
Linux
1) Install Git and Build tools
# sudo apt update
# sudo apt install git build-essential curl zip unzip

2) Clone vcpkg
# git clone https://github.com/microsoft/vcpkg.git
# cd vcpkg

3) Bootstrap vcpkg
# ./bootstrap-vcpkg.sh

4) Install Postgre SQL Client Library
# ./vcpkg install libpq:x64-linux

5) Install libpqxx(C++ wrapper)
# ./vcpkg install libpqxx:x64-linux
-------------------------------------------------------------------------------------------------------

-------------------------------------------------------------------------------------------------------
MacOS
1) Install XCode Command Tool
# xcode-select --install

2) Install git
# brew install git

3) CLone and bootstrap vcpkg
# git clone https://github.com/microsoft/vcpkg.git
# cd vcpkg
# ./bootstrap-vcpkg.sh

4) Install PostgreSQL library client
# ./vcpkg install libpq:x64-osx

5) Install libpqxx
# ./vcpkg install libpqxx:x64-osx

-- To install  nlohmann-json(handle json objects)
# vcpkg install nlohmann-json:x64-windows

For linux and MacOS use:
# ./vcpkg install nlohmann-json:x64-linux
# ./vcpkg install nlohmann-json:x64-osx

------------------------------------------------------------------------------------------------------

# Create a PostgreSQL Database(Navigate to the cli-health assistant)
# i) Login in as the default PostgreSQL superuser(postgres)
# sudo -u postgres psql 

# ii) Create a New Role
# Create the role: CREATE USER health WITH PASSWORD '2005';

# Create the database: CREATE DATABASE health_assistant WITH OWNER health

-- Granting Priviledge to the USER
# GRANT ALL PRIVILEGES ON patients TO health;

-- Grant USAGE on the sequence for the 'id' column to the 'health' user
# GRANT USAGE ON SEQUENCE patients_id_seq TO health;

-- verify Permissions
# \z patients

Connect to the new database
# \c health_assistant

# Create tables: Patient table: CREATE TABLE patients ( id SERIAL PRIMARY KEY, name VARCHAR(255) NOT NULL, age INT, height DOUBLE PRECISION, condition VARCHAR(255), nutrition JSONB, fitness JSONB, mental_status JSONB, skincare JSONB );

Verify the table creation: \dt

To access the database:
# sudo -u postgres psql -d health_assistant

To exit the database
# \quit

# CONNECTING TO THE DATABASE USING POSTGRESQL EXTENSION FROM VISUAL STUDIO CODE(Graphical User Interface)
# The PostgreSQL extension for Visual Studio Code is a powerful tool:
# 1. Install the extension in VSCode: Go to the extension tab and install PostgreSQL by microsoft(Database Client)

# Connect to the Database
# Click the PostgreSQL icon in the Activity Bar in the Left
# Click Add connection button
# Enter connection details(host, username, password, database name)



-------------------------------------------------------------------------------------------------------
Compile the Project
Navigate to the src folder
# Use the following command: g++ -o health_assistant main.cpp patient.cpp db_postgres.cpp nutrition.cpp fitness.cpp mental_status.cpp skincare.cpp utils.cpp -I/usr/include/postgresql -lpqxx -lpq

# 2. Run the command line application and perform operations through the CLI
# Execute the compiled program by running the following: 
  ./health_assistant








  











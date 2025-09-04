⚕️ C++ Health Assistant Command Line Application
This repository contains a C++ console application that demonstrates Basic CRUD (Create, Read, Update, Delete) Operations on patient records, backed by a PostgreSQL database. The project uses libpqxx for database connectivity and nlohmann-json for handling structured data.

🎯 Project Overview
This application functions as a simple health assistant, allowing users to manage patient data directly from the command line. It supports the following operations:

Add a new patient record with details on nutrition, fitness, mental status, and skincare.

Retrieve a patient's information using their ID.

Update an existing patient's data.

Delete an existing patient record.

List all patients currently in the database.

A modern approach to data modeling is used, where the patient's health data (nutrition, fitness, etc.) is stored in a structured JSONB column within the PostgreSQL table.

🚀 Getting Started
Prerequisites
To get the application up and running, you'll need the following installed on your system:

PostgreSQL: A running instance of the PostgreSQL database server.

C++ Compiler: A compiler that supports C++11 or newer (e.g., g++ or clang++).

vcpkg: This is the recommended package manager for easily installing the required C++ libraries (libpqxx and nlohmann-json).

Setup and Installation
1. Clone the Repository
First, clone the project from its GitHub repository:

Bash

git clone <repository_url>
cd <repository_name>
🛠️ Installation of Dependencies
PostgreSQL
🌐 Cross-Platform Installation
Windows

Download Installer: Go to the official PostgreSQL download page and get the interactive installer by Enterprise DB.

Run Installer: The installer will guide you. Choose the components to install (PostgreSQL Server, pgAdmin, Stack Builder) and set a strong password for the postgres superuser.

Start Server: The installer typically sets up PostgreSQL as a Windows Service, so it will start automatically.

Linux (Debian/Ubuntu)

Update package lists: sudo apt update

Install PostgreSQL: sudo apt install postgresql postgresql-contrib

Start and enable the service:

Bash

sudo systemctl start postgresql
sudo systemctl enable postgresql
Linux (RedHat/Fedora)

Install PostgreSQL: sudo dnf install postgresql-server

Initialize the database cluster: sudo postgresql-setup --initdb

Start and enable the service:

Bash

sudo systemctl start postgresql
sudo systemctl enable postgresql
macOS

Homebrew (Recommended): If not already installed, get it from brew.sh.

Install PostgreSQL: brew install postgresql

Start the service: brew services start postgresql

C++ Compiler and Visual Studio Code
💻 Visual Studio Code Setup
Install the C/C++ and C++ Intellisense extensions from the VS Code Marketplace for a better development experience.

Windows
Install the MinGW-w64 compiler by downloading the installer from the official site. Remember to add the bin directory of the MinGW-w64 installation to your system's PATH environment variable.

Linux
Install g++ and other build tools with a single command:
sudo apt update && sudo apt install build-essential

macOS
Install the Xcode Command Line Tools, which include g++ and clang++ compilers:
xcode-select --install

📦 Installing C++ Libraries with vcpkg
vcpkg is a crucial tool for managing the required libraries.

1. Install vcpkg
Windows

Bash

git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install
Add the vcpkg directory to your system's PATH.

Linux

Bash

git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
macOS

Bash

git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.sh
2. Install Project Libraries
Use vcpkg to install the necessary libraries for your operating system:

libpqxx (C++ wrapper for PostgreSQL)

Windows: vcpkg install libpqxx:x64-windows

Linux: ./vcpkg install libpqxx:x64-linux

macOS: ./vcpkg install libpqxx:x64-osx

nlohmann-json (JSON library)

Windows: vcpkg install nlohmann-json:x64-windows

Linux: ./vcpkg install nlohmann-json:x64-linux

macOS: ./vcpkg install nlohmann-json:x64-osx

⚙️ Database Configuration
1. Create the Database and User
Navigate to the project's root directory and run the following commands in your terminal to set up the database and user.

Bash

# Login as the postgres superuser
sudo -u postgres psql

# Create a new user with a password
CREATE USER health WITH PASSWORD '2005';

# Create the database and assign ownership
CREATE DATABASE health_assistant WITH OWNER health;

# Connect to the new database
\c health_assistant

# Create the patients table
CREATE TABLE patients (
    id SERIAL PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    age INT,
    height DOUBLE PRECISION,
    condition VARCHAR(255),
    nutrition JSONB,
    fitness JSONB,
    mental_status JSONB,
    skincare JSONB
);

# Grant privileges to the user
GRANT ALL PRIVILEGES ON patients TO health;
GRANT USAGE ON SEQUENCE patients_id_seq TO health;

# Verify the table creation and permissions
\dt
\z patients

# Exit the database shell
\q
2. Connect via VS Code Extension (Optional)
You can also use the PostgreSQL extension in Visual Studio Code for a more graphical way to manage your database:

Install the "PostgreSQL" extension by Microsoft.

Click the PostgreSQL icon in the Activity Bar.

Click "Add connection" and enter your database details (host, user, password, database name).

▶️ Running the Application
Compile the Project
Navigate to the src directory and use the following command to compile the source files. Make sure the paths to your libraries are correct.

Bash

g++ -o health_assistant main.cpp patient.cpp db_postgres.cpp nutrition.cpp fitness.cpp mental_status.cpp skincare.cpp utils.cpp -I/usr/include/postgresql -lpqxx -lpq
Execute the Program
Once compiled, run the application from the command line:

Bash

./health_assistant
You can now interact with the C++ Health Assistant through the command-line interface.
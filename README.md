# Health Assistant CLI

A comprehensive C++ command-line application for managing patient health records with integrated PostgreSQL database support. This application provides a complete health management system covering nutrition, fitness, mental health, and skincare tracking.

## 🚀 Features

- **Patient Management**: Complete CRUD operations for patient records
- **Health Tracking**: Monitor nutrition, fitness, mental status, and skincare
- **Database Integration**: PostgreSQL backend with JSONB support for structured health data
- **Interactive CLI**: User-friendly command-line interface
- **Data Validation**: Built-in validation for health metrics and patient data
- **Cross-Platform**: Supports Windows, Linux, and macOS

## 🔧 Prerequisites

Before you begin, ensure you have the following installed:

- **PostgreSQL** (version 12 or higher)
- **C++ Compiler** with C++11 support or newer
- **vcpkg** (recommended for package management)
- **Git**

## 🛠️ Installation

### 1. Clone the Repository

```bash
git clone https://github.com/Victor-creat-alt/health-assistant.git
cd health-assistant
```

### 2. Install PostgreSQL

## Windows

1. Download the PostgreSQL installer from the [official website](https://www.postgresql.org/download/windows/)
2. Run the installer and follow the setup wizard
3. Set a strong password for the `postgres` superuser
4. Use the default port (5432)
5. The service will start automatically

### Linux (Ubuntu/Debian)

```bash
sudo apt update
sudo apt install postgresql postgresql-contrib
sudo systemctl start postgresql
sudo systemctl enable postgresql
```

### Linux (RedHat/Fedora)

```bash
sudo dnf install postgresql-server
sudo postgresql-setup --initdb
sudo systemctl start postgresql
sudo systemctl enable postgresql
```

### macOS

```bash
# Using Homebrew
brew install postgresql
brew services start postgresql
```

### 3. Install Development Tools

#### Windows Platform

1. Install MinGW-w64 from the [official site](https://www.mingw-w64.org/)
2. Add MinGW-w64 bin directory to your system PATH
3. Install Visual Studio Code with C/C++ extensions

#### Linux

```bash
# Ubuntu/Debian
sudo apt update && sudo apt install build-essential

# RedHat/Fedora
sudo dnf groupinstall "Development Tools"
```

## macOS Platform

```bash
xcode-select --install
```

### 4. Install Dependencies with vcpkg

#### Setup vcpkg

```bash
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg

# Windows
.\bootstrap-vcpkg.bat
.\vcpkg integrate install

# Linux/macOS
./bootstrap-vcpkg.sh
```

#### Install Required Libraries

```bash
# Windows
.\vcpkg install libpq:x64-windows
.\vcpkg install libpqxx:x64-windows
.\vcpkg install nlohmann-json:x64-windows

# Linux
./vcpkg install libpq:x64-linux
./vcpkg install libpqxx:x64-linux
./vcpkg install nlohmann-json:x64-linux

# macOS
./vcpkg install libpq:x64-osx
./vcpkg install libpqxx:x64-osx
./vcpkg install nlohmann-json:x64-osx
```

## 🗄️ Database Setup

### 1. Create Database and User

```sql
-- Connect as postgres superuser
sudo -u postgres psql

-- Create user and database
CREATE USER health WITH PASSWORD '2005';
CREATE DATABASE health_assistant WITH OWNER health;

-- Grant privileges
GRANT ALL PRIVILEGES ON DATABASE health_assistant TO health;
```

### 2. Create Patient Table

```sql
-- Connect to the health_assistant database
\c health_assistant

-- Create the patients table
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

-- Grant table permissions
GRANT ALL PRIVILEGES ON patients TO health;
GRANT USAGE ON SEQUENCE patients_id_seq TO health;

-- Verify table creation
\dt
```

### 3. Verify Database Connection

```bash
# Test connection
psql -h localhost -U health -d health_assistant
```

## 🔨 Building the Project

Navigate to the source directory and compile:

```bash
cd cli-health-assistant/src

# Compile the application
g++ -o health_assistant main.cpp patient.cpp db_postgres.cpp nutrition.cpp fitness.cpp mental_status.cpp skincare.cpp utils.cpp -I/usr/include/postgresql -lpqxx -lpq

# Make executable (Linux/macOS)
chmod +x health_assistant
```

## 🚀 Usage

Run the compiled application:

```bash
./health_assistant
```

### Menu Options

The application provides an interactive menu with the following options:

1. **Add Patient** - Create a new patient record with comprehensive health data
2. **View Patient Details** - Retrieve and display patient information by ID
3. **Update Patient Information** - Modify existing patient records
4. **Delete Patient Record** - Remove a patient from the database
5. **List All Patients** - Display all patients in the system
6. **Exit** - Close the application

### Example Usage

``` Health Assitant
Health Assistant Menu:
1. Add Patient
2. View Patient Details
3. Update Patient Information
4. Delete Patient record
5. List All Patients
6. Exit
Enter your choice: 1

Enter patient ID: 1
Enter patient name: John Doe
Enter patient age: 30
Enter patient height (in cm): 175
Enter mental condition (e.g Depression, Anxiety): None

--- Enter Nutrition Details ---
Enter daily calories: 2000
Enter daily protein (g): 150
Enter daily carbs (g): 250
Enter daily fats (g): 70
Enter diet type (e.g. Vegetarian, Vegan, Keto): Balanced

--- Enter Fitness Details ---
Enter steps per day: 10000
Enter exercise minutes per day: 60
Enter activity type (e.g Running, Cycling): Running
Enter fitness goals (e.g Weight Loss, Muscle Gain, Maintenance): Maintenance
Enter workout routine (e.g Cardio, Strength Training): Cardio

--- Enter Mental Status Details ---
Enter mood level (1-10): 8
Enter stress level (Low, Medium, High): Low
Enter sleep quality (Poor, Average, Good): Good

--- Enter Skin Care Details ---
Enter skin type (e.g Oily, Dry, Combination): Normal
Enter Skin concerns (e.g Acne, Aging, Sensitivity): None
Enter skin care routine (e.g Cleansing, Moisturization): Daily
Enter products used (e.g Cleanser, Toner, Moisturizer): Cleanser
Enter skin care goals (e.g Clear Skin, Hydration, Anti-Aging): Maintenance

Patient added successfully.
```

## 📁 Project Structure

``` Folder structure
health-assistant/
├── README.md
├── Command Line Application.pdf
└── cli-health-assistant/
    └── src/
        ├── main.cpp              # Main application entry point
        ├── patient.h/cpp         # Patient data structure and operations
        ├── db_postgres.h/cpp     # PostgreSQL database operations
        ├── nutrition.h/cpp       # Nutrition tracking functionality
        ├── fitness.h/cpp         # Fitness monitoring features
        ├── mental_status.h/cpp   # Mental health status tracking
        ├── skincare.h/cpp        # Skincare routine management
        ├── utils.h/cpp           # Utility functions
        └── CMakeList.txt         # Build configuration
```

## 🏗️ Architecture

The application follows a modular design pattern:

- **Database Layer**: PostgreSQL with libpqxx for C++ integration
- **Data Models**: Structured C++ classes for different health aspects
- **Business Logic**: Separate modules for each health domain
- **User Interface**: Interactive command-line interface
- **Data Storage**: JSONB format for flexible health data storage

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🐛 Troubleshooting

### Common Issues

1. **Database Connection Failed**
   - Verify PostgreSQL is running
   - Check connection parameters in `main.cpp`
   - Ensure user `health` has proper permissions

2. **Compilation Errors**
   - Verify all dependencies are installed via vcpkg
   - Check compiler version supports C++11
   - Ensure PostgreSQL headers are in include path

3. **Runtime Errors**
   - Check database exists and is accessible
   - Verify table structure matches application expectations
   - Ensure proper permissions on database objects

### Getting Help

- Check the [Issues](https://github.com/Victor-creat-alt/health-assistant/issues) page
- Review the documentation in `Command Line Application.pdf`
- Ensure all prerequisites are properly installed

## 📊 Health Data Structure

The application stores comprehensive health data in JSONB format:

- **Nutrition**: Calories, macronutrients, diet type
- **Fitness**: Daily steps, exercise duration, activity types, goals
- **Mental Status**: Mood levels, stress indicators, sleep quality
- **Skincare**: Skin type, concerns, routines, products used

This flexible structure allows for easy extension and modification of health tracking parameters.

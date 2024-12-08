#ifndef CONNECTION_H
#define CONNECTION_H

#include <QSqlDatabase>

class Connection {
public:
    Connection();  // Constructor
    ~Connection(); // Destructor (explicitly declared)

    bool createConnection(); // Function to create a connection

private:
    QSqlDatabase db; // Database connection object
};

#endif // CONNECTION_H

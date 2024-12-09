#include "arduino.h"

Arduino::Arduino()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *Arduino::getserial()
{
    return serial;
}
int Arduino::connect_arduino()
{
    // Debug: List all available serial ports
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Available Port: " << serial_port_info.portName();

        if (serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()) {
            if (serial_port_info.vendorIdentifier() == arduino_uno_vendor_id &&
                serial_port_info.productIdentifier() == arduino_uno_producy_id) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                break;  // Exit loop once the correct port is found
            }
        }
    }

    if (arduino_is_available) {
        qDebug() << "Arduino found on port: " << arduino_port_name;

        // Set the correct port for communication
        serial->setPortName(arduino_port_name);

        // Try to open the serial port
        if (serial->open(QSerialPort::ReadWrite)) {
            qDebug() << "Successfully connected to Arduino.";
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return 0;  // Success
        } else {
            qDebug() << "Failed to open port: " << serial->errorString();
            return 1;  // Failed to open port
        }
    } else {
        qDebug() << "Arduino not found. Please check the connection and try again.";
        return -1;  // Arduino not found
    }
}



int Arduino::close_arduino()

{

    if(serial->isOpen()){
        serial->close();
        return 0;
    }
    return 1;


}


QByteArray Arduino::read_from_arduino()
{
    if(serial->isReadable()){
        data=serial->readAll(); //récupérer les données reçues

        return data;
    }
}


void Arduino::write_to_arduino( QByteArray d)

{

    if(serial->isWritable()){
        serial->write(d);  // envoyer des donnés vers Arduino
    }else{
        qDebug() << "Couldn't write to serial!";
    }


}

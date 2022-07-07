using UnityEngine;
using System.IO.Ports;

public class SerialCommunication : MonoBehaviour {

    SerialPort sp;
    int baud = 115200;
    int com = "COM3";

    void Start() {
        sp = new SerialPort("\\\\.\\" + com, baud);
        sp.Open();
        sp.ReadTimeOut = 1;
    }

    void Update() {

        int recFromArduino = 0;
        
        try {
            recFromArduino = sp.ReadLine();
            Debug.Log(recFromArduino);
        } catch (System.Expception e) {
            Debug.Log(e.ToString());
        }
    }
}
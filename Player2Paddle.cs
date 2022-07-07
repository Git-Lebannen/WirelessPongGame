using UnityEngine;
using System.IO.Ports;

public class Player2Paddle : MonoBehaviour {

    public GameObject SerialComm;

    public float speed;
    public Rigidbody2D rb;
    public Vector3 startPosition;

    private float movement;
    private int input;

    void Start() {
        startPosition = transform.position;
    }

    void Update() {

        // wertet Input vom Arduino aus
        input = SerialComm.GetComponent<SerialCommunication>().recFromArduino;

        if (input == 21)
            movement = 5;
        else if (input == 22)
            movement = -5;
        else
            movemen = 0;

        rb.velocity = new Vector2(0, movement * speed * Time.deltaTime);

    }

    public void Reset() {
        rb.velocity = Vector2.zero;
        transform.position = startPosition;
    }
    
}
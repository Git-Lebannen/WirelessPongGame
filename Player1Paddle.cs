using UnityEngine;
using System.IO.Ports;

public class Player1Paddle : MonoBehaviour {

    public GameObject serialComm;

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
        input = serialComm.GetComponent<SerialCommunication>().recFromArduino;

        if (input == 11)
            movement = 5;
        else if (input == 12)
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
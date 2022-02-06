using UnityEngine;

public class Player1Movement : MonoBehaviour {

    public Rigidbody2D rb;
    public Vector2 startPos;
    public float speed;

    float yPos = 0.0f;
    int inpY;

    void Update() {

        inpY = (int) Mathf.Round(Input.GetAxis("P1"));

        //Debug.Log(inpY);

        yPos += inpY * speed * Time.deltaTime;

        if (yPos > 4 || yPos < -4)
            yPos -= inpY * speed * Time.deltaTime;

        transform.position = new Vector2(-9, yPos);
    }

    public void Reset() {
        transform.position = startPos;
    }
}
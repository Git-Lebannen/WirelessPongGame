using UnityEngine;

public class BallMovement : MonoBehaviour {

    public Rigidbody2D rb;
    public Vector2 startPos;

    float v, x, y;

    void Start() {
        Launch();
    }

    void Launch() {
        v = 120;       
        x = Random.Range(0, 2) == 0 ? -1 : 1;
        y = Random.Range(0, 2) == 0 ? -1 : 1;
        rb.velocity = new Vector2(v * x * Time.deltaTime, v * y * Time.deltaTime);
    }

    public void Reset() {
        rb.velocity = Vector2.zero;
        transform.position = startPos;
        Launch();
    }
}
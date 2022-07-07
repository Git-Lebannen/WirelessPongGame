using UnityEngine;

public class Goal : MonoBehaviour {

    public bool isPlayer1Goal;

    private void OnTriggerenter2D(Collider2D collision) {

        // wenn ein Tor erzielt wurde
        // wendet sich das Script an den GameManager
        // um den Torschützen zu identifizieren
        if (collision.gameObject.CompareTag("Ball")) {

            if (!isPlayer1Goal) {
                Debug.Log("Player 1 Scored...");
                GameObject.Find("GameManager").GetComponent<GameManager>().Player2Scored();
            } else {
                Debug.Log("Player 2 Scored...");
                GameObject.Find("GameManager").GetComponent<GameManager>().Player1Scored();
            }

        }
    }

}
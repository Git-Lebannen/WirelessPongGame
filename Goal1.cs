using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Goal1 : MonoBehaviour {

    private void OnTriggerEnter2D(Collider2D coll) {
        
        if (coll.gameObject.CompareTag("Ball")) {
            GameObject.Find("GameManager").GetComponent<GameManager>().Player2Scored();
        }    
    }
}
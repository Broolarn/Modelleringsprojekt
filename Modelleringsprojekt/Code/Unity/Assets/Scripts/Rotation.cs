using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rotation : MonoBehaviour {
    public static float radie = 0.025f;
    public static float b = 0.0002f;
    public static float m1 = 0.024f;
    public static float hojd = 0.05f;
    private static float airmy = 1.846f;

    private static float Mluft = 2 * Mathf.PI * airmy * radie * hojd / 3;

    private float lambda = (3.0f / 10.0f) * m1 * Mathf.Pow(radie, 2.0f) - (b / m1) - Mluft;
    private float h = 1.0f / 60.0f;
    private int i = 0;

    public float oldOmega = 271.0f;
    private float oldOmegaP = 0.0f;
    private float currAngle = 0.0f;
    private float currAngleP = 0.0f;

    private Rigidbody rb;

    // Use this for initialization
    void Start () {
        
    }
	
	// Update is called once per frame
	void Update () {
        float newOmega = oldOmega + h * lambda * oldOmega;
        currAngle = oldOmega * h;
        float angle = currAngle * (180.0f / Mathf.PI);

        Vector3 movement = new Vector3(0.0f, currAngle, 0.0f);
        
        transform.Rotate(Vector3.up * angle);

        oldOmega = newOmega;
    }
}

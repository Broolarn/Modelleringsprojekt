using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Translation : MonoBehaviour {

    private static float g = 9.82f;
    public static float oldPhiv = Mathf.PI/4.0f;
    private static float r = 0.2f;
    private static float h = 1.0f / 60.0f;
    private static float oldPhi = Mathf.PI/4.0f;
    private static float oldW = 0.0f;
    public static float m = 0.025f;
    private static float b = 0.2f;
    private static float oldTheta = Mathf.Atan(1.75f);// (r - 0.025f) * 10.0f;

    private Rigidbody rb;

	// Use this for initialization
	void Start () {
        rb = GetComponent<Rigidbody>();
	}
	
	// Update is called once per frame
	void Update () {
 
            if (oldPhi < Mathf.Pow(10, 18) && oldTheta < Mathf.Pow(10, 18) && oldPhiv < Mathf.Pow(10, 18))
            {
                float Phia = oldPhiv / r;
                float newPhiv = oldPhiv + h * Phia;

                float newPhi = oldPhi + newPhiv * h;

                float a = -g * Mathf.Sin(oldTheta) / r;
                float newW = oldW + a * h - (0.2f / m) * oldW;
                float newTheta = oldTheta + newW * h;


                float X = (4.0f * r * Mathf.Sin(oldTheta) * Mathf.Cos(oldPhi));
                float Y = (4.0f * r * Mathf.Sin(oldTheta) * Mathf.Sin(oldPhi));
                float Z = (1.0f * -r * Mathf.Cos(oldTheta));

                //rb.AddForce(movement);

                transform.position = new Vector3(X, Z, Y);

                float rotPhi = newPhiv * h;
                transform.Rotate(Vector3.up * rotPhi);

                float rotTheta = newW * h;
                transform.Rotate(Vector3.forward * rotTheta);

                oldPhiv = newPhiv;
                oldPhi = newPhi;
                oldTheta = newTheta;
            
        }
    }
}

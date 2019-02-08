using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Collision1 : MonoBehaviour
{

    private static float r = 0.025f;
    private static float mA = 0.024f;
    private static float mB = 0.034f;

    private static float IA = mA * r * (3.0f / 10.0f);
    private static float IB = mB * r * (3.0f / 10.0f);

    public static float v1A = -2.0f;
    public static float v1B = 1.0f;
    private static float v1AB = v1A - v1B;



    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        transform.position = new Vector3(transform.position.x + v1B / 60.0f, 0.0f, 0.0f);

    }

   /* void onTriggerEnter(Collider other)
    {
        Vector3 n = new Vector3(1.0f, 0.0f, 0.0f);
        Vector3 rAP = new Vector3(0.025f, 0.0f, 0.05f);
        Vector3 rBP = new Vector3(-0.025f, 0.0f, 0.05f);
        Vector3 j = (-2 * v1AB * n) / (Vector3.Dot(n, n) * (1.0f / mA + 1.0f / mB) + (Mathf.Pow(Vector3.Dot(rAP, n), 2.0f) / IA) + (Mathf.Pow(Vector3.Dot(rBP, n), 2.0f) / IB));

        float v2B = v1B + Vector3.Dot(j, n) / mB;
        v1B = v2B;

    }*/
}
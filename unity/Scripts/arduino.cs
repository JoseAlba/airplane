using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;
using System.Threading;

public class arduino : MonoBehaviour {

	public static SerialPort sp = new SerialPort ("COM4", 9600);
	public string message2;
	float timepassed = 0.0f;
	// Use this for initialization
	void Start () {
		OpenConnection ();
	}
	
	// Update is called once per frame
	void Update () {
		message2 = sp.ReadLine ();
		print (message2);
	}

	public void OpenConnection(){
	
		if (sp != null) {
			if (sp.IsOpen) {
				sp.Close ();
				print ("Closing Port, because it was already open");
			} else {
				sp.Open ();
				sp.ReadTimeout = 16;
				print ("Port Opened");
			}
		} else {
			if (sp.IsOpen) {
				print ("Port is already open");
			} else {
				print ("Port == null");
			}
		}
	}

	void onApplicationQuit(){
		sp.Close();
	}
}

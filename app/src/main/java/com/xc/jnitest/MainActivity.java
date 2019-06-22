package com.xc.jnitest;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.xc.jnitest.exercise.JniTest;

public class MainActivity extends AppCompatActivity {


    TextView mText;

    int[] array = new int[]{1, 2, 3, 4, 5};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mText = findViewById(R.id.textview1);

        JniTest jniTest = new JniTest();

        mText.setText(jniTest.get());

        jniTest.set("This is a incoming parameter");

//        int[] newArray = jniTest.formatArray(array);
//
//        for (int i = 0; i < newArray.length; i++) {
//            Log.i("MainActivity", "i=" + newArray[i]);
//        }
    }
}

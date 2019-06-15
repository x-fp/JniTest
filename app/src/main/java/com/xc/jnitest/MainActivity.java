package com.xc.jnitest;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.xc.jnitest.exercise.JniTest;

public class MainActivity extends AppCompatActivity {


    TextView mText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mText = findViewById(R.id.textview1);

        JniTest jniTest = new JniTest();
        
        mText.setText(jniTest.get());
    }
}

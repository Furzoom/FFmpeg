package com.furzoom.lab.ffmpeg;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private Button protocol;
    private TextView tv;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        protocol = (Button) findViewById(R.id.btn_protocol);
        protocol.setOnClickListener(this);
        tv = (TextView) findViewById(R.id.sample_text);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native String urlprotocolinfo();
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.btn_protocol:
                tv.setText(urlprotocolinfo());
                break;
            default:
                break;
        }
    }
}

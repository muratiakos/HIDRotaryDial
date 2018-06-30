package com.murati.phone.rotarydialer;

import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.KeyEvent;
import android.widget.TextView;
import android.widget.Toast;

public class DialerActivity extends AppCompatActivity {
    private static String LOG_TAG = "DIALER";

    private TextView outputView;
    private String dialNumber = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_dialer);

        //Dialer output
        outputView = findViewById(R.id.outputView);
        outputView.setText("");
    }

    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event) {
        switch(keyCode) {
            case KeyEvent.KEYCODE_0:
            case KeyEvent.KEYCODE_1:
            case KeyEvent.KEYCODE_2:
            case KeyEvent.KEYCODE_3:
            case KeyEvent.KEYCODE_4:
            case KeyEvent.KEYCODE_5:
            case KeyEvent.KEYCODE_6:
            case KeyEvent.KEYCODE_7:
            case KeyEvent.KEYCODE_8:
            case KeyEvent.KEYCODE_9:
                dialNumber += String.valueOf(keyCode-7);
                break;
            case KeyEvent.KEYCODE_DEL:
                if (dialNumber.length() >= 1) {
                    dialNumber = TextUtils.substring(dialNumber, 0, dialNumber.length() - 1);
                }
                break;

            case KeyEvent.KEYCODE_ENTER:
                dialNumber();
            case KeyEvent.KEYCODE_MOVE_END:
            case KeyEvent.KEYCODE_ESCAPE:
            case KeyEvent.KEYCODE_CLEAR:
                dialNumber = "";
                break;
            default:
                //NOOP
        }
        outputView.setText(dialNumber);
        Log.i(LOG_TAG,"Key pressed: " + String.valueOf(keyCode));
        return super.onKeyUp(keyCode, event);
    }

    private void dialNumber() {
        String message = "";
        if (dialNumber.length() < 3) {
            message = "Number is too short to dial";
            return;
        }

        try {
            message = "Dialing " + dialNumber;
            startActivity(new Intent(Intent.ACTION_CALL, Uri.parse("tel:" + dialNumber)));
        }
        catch (SecurityException ex) {
            Log.e(LOG_TAG, ex.getMessage());
            message = ex.getMessage();
        }
        catch (Exception ex) {
            Log.e(LOG_TAG, ex.getMessage());
            message = ex.getMessage();
        }

        if (message != "")
            Toast.makeText(this, message, Toast.LENGTH_LONG);
    }
}

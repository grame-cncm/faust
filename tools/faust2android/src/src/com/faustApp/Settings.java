package com.faustApp;

import android.os.Bundle;
import android.app.ListActivity;
import android.content.Intent;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.ListView;

public class Settings extends ListActivity {

	public void onCreate(Bundle icicle) {
	    super.onCreate(icicle);
	    String[] values = new String[] { "Audio", "OSC", "About" };
	    ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
	        android.R.layout.simple_list_item_1, values);
	    setListAdapter(adapter);
	  }
	
	@Override
	  protected void onListItemClick(ListView l, View v, int position, long id) {
	    String item = (String) getListAdapter().getItem(position);
	    if(item == "Audio"){
	    	Intent audioIntent = new Intent(this, AudioSettings.class);
	    	startActivity(audioIntent);
	    }
	    else if(item == "OSC"){
	    	Intent helpIntent = new Intent(this, OSCSettings.class);
	    	startActivity(helpIntent);
	    }
	    else if(item == "About"){
	    	Intent helpIntent = new Intent(this, About.class);
	    	startActivity(helpIntent);
	    }
	  }

}

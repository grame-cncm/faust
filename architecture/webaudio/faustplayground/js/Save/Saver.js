"use strict";


function saveScene(scene){
	
	var modules = scene.getModules();
	
	for(var i=0; i<modules.length; i++){
		modules[i].patchID = i+1;
	}
	
	scene.audioOutput().patchID = 0;
	
	var json = '{';

	for(var i=0; i<modules.length; i++){
		if(i != 0)
			json+=',';
			
		json += '"' + modules[i].patchID.toString() + '":['
		
		json += '{"x":"' + modules[i].getContainer().getBoundingClientRect().left+ '"},';
		json += '{"y\":"' + modules[i].getContainer().getBoundingClientRect().top + '"},';
		json += '{"name\":"' + modules[i].getName() + '"},';
		json += '{"code":' + JSON.stringify(modules[i].getSource()) + '},';
		
		var inputs = modules[i].getInputConnections();
		
		if(inputs){
		
			json += '{"inputs":[';
			for(var j=0; j<inputs.length; j++){
				if(j !=0)
					json+=',';		
			
				json += '{"src":"' + inputs[j].source.patchID.toString() + '"}';
			}
			json += ']},';
		}
		
		var outputs = modules[i].getOutputConnections() ;
		if(outputs){
			json += '{"outputs":[';		

	
			for(var j=0; j<outputs.length; j++){
				if(j !=0)
					json+=',';		
			
				json += '{"dst":"' + outputs[j].destination.patchID.toString() +'"}';
			}		

			json += ']},';
		}
		
		var params = modules[i].getDSP().controls();
		if(params){
			json += '{"params":[';		
	
			for(var j=0; j<params.length; j++){
				if(j !=0)
					json+=',';		
			
				json += '{"path":"' + params[j] +'"},';
				json += '{"value":"' + modules[i].getDSP().getValue(params[j]) +'"}';
			}		

			json += ']}';
		}
		
		json += ']';
	}

	json += '}';
	
	console.log(json);
// 	recallScene(json);
	return json;

}

function createModuleAndConnectIt(factory){

	if (!factory) {
    	alert(faust.getErrorMessage());    
        return null;
	}
        
	var faustModule;

	if(isTooltipEnabled())
		faustModule = createNode(idX++, window.x, window.y, window.name, document.getElementById("modules"), window.scenes[1].removeModule);
 	else
 		faustModule = createNode(idX++, window.x, window.y, window.name, document.getElementById("modules"), window.scenes[0].removeModule);

 	faustModule.setSource(window.source);
 	faustModule.setDSP(factory); 	
 	
 	if(window.params){
		for(var i=0; i<window.params.length; i++){
			console.log(window.params);
			if(window.params[i] && window.params[i+1]){
				faustModule.addParam(window.params[i]["path"], window.params[i+1]["value"]);
				i+1;
			}	
		}
		faustModule.recallParams();
	}
 	
 	
	faustModule.createInterface();
 	faustModule.addInputOutputNodesToModule();
 		
 	window.scenes[window.currentScene].addModule(faustModule);
	
// WARNING!!!!! Not right in an asynchroneous call of compileFaust
	if(window.inputs){
		for(var i=0; i<window.inputs.length; i++){
			console.log(window.inputs[i]["src"]);
		
			var src = window.scenes[window.currentScene].getModules()[window.inputs[i]["src"]-1];
			if(src)
				createConnection(src, src.getOutputNode(), faustModule, faustModule.getInputNode());	
		}
	}
	
	if(window.outputs){
		for(var i=0; i<window.outputs.length; i++){
				console.log(window.outputs[i]["dst"]);
			var dst = window.scenes[window.currentScene].getModules()[window.outputs[i]["dst"]-1];

			if(dst)
				createConnection(faustModule, faustModule.getOutputNode(), dst, dst.getInputNode());
				
			else if(window.outputs[i]["dst"] == 0){
				console.log(window.scenes[1].audioOutput());
				createConnection(faustModule, faustModule.getOutputNode(), window.scenes[window.currentScene].audioOutput(), window.scenes[window.currentScene].audioOutput().getInputNode());
			}
		}
	}
}

function recallScene(json){

	var data = JSON.parse(json);
	
	var sel;	
	for(sel in data){
						
	    var dataCopy = data[sel];
    
		var newsel;
		var name, code, x, y;

		for (newsel in dataCopy) {
				var mainData = dataCopy[newsel];
        		if(mainData["name"])
					name = mainData["name"];
        		else if(mainData["code"])
        			code = mainData["code"];
        		else if(mainData["x"])
        			x = mainData["x"];
        		else if(mainData["y"])
        			y = mainData["y"];
        		else if(mainData["inputs"])
        			window.inputs = mainData["inputs"];
        		else if(mainData["outputs"])
        			window.outputs = mainData["outputs"];
        		else if(mainData["params"])
        			window.params = mainData["params"];
		}	
		compileFaust(name, code, x, y, createModuleAndConnectIt);
	}		
}


// PAS FUNCTIONNEL 
function createMailServer(){
	
	var http   = require('http'),
	qs         = require('querystring'),
	nodemailer = require('nodemailer');

	var transporter = nodemailer.createTransport({
	  service: 'Gmail',
	  auth: {
	    user: 'myemail@gmail.com',
    	pass: 'myGmailPassword'
	  }
	});

	var server = http.createServer(function(req, res) {
	  if (req.method === 'POST' && req.url === '/') {
    	var body = '';
	    req.on('data', function (data) {
    	  body += data;
	    });

    	req.on('end', function () {
	      var mail = qs.parse(body);

    	  var mailOptions = {
	        from: mail.name+' <'+ mail.sender +'>',
        	to: 'myAdress@anything.com',
    	    subject: 'Contact ',
	        text: mail.message,
        	html: mail.message
    	  };

	      transporter.sendMail(mailOptions, function(err, response){
    	    !!err ? console.error(err) : res.end();
	      });
    	});
	  }
	  res.end();
	});

	server.listen(1337);
}
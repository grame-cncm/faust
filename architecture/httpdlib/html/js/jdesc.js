
function getDesc() {
	return '{\
	"name": "karplus",\
	"address": "localhost",\
	"port": "5510",\
	"ui": [\
		{\
			"type": "horizontalslider",\
			"label": "excitation",\
			"address": "/karplus/excitator/excitation",\
			"init": "128",\
			"min": "2",\
			"max": "512",\
			"step": "1"\
		},\
		{\
			"type": "button",\
			"label": "play",\
			"address": "/karplus/excitator/play"\
		},\
		{\
			"type": "horizontalslider",\
			"label": "level",\
			"address": "/karplus/level",\
			"init": "0.5",\
			"min": "0",\
			"max": "1",\
			"step": "0.1"\
		},\
		{\
			"type": "horizontalslider",\
			"label": "attenuation",\
			"address": "/karplus/resonator/attenuation",\
			"init": "0.1",\
			"min": "0",\
			"max": "1",\
			"step": "0.01"\
		},\
		{\
			"type": "horizontalslider",\
			"label": "duration",\
			"address": "/karplus/resonator/duration",\
			"init": "128",\
			"min": "2",\
			"max": "512",\
			"step": "1"\
		}\
	]\
}';
}

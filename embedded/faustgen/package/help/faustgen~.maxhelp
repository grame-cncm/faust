{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 6,
			"minor" : 1,
			"revision" : 9,
			"architecture" : "x64"
		}
,
		"rect" : [ 216.0, 92.0, 1337.0, 762.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 0,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 0,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"boxanimatetime" : 200,
		"imprint" : 0,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"showrootpatcherontab" : 0,
		"showontab" : 0,
		"boxes" : [ 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-8",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 1,
							"revision" : 9,
							"architecture" : "x64"
						}
,
						"rect" : [ 0.0, 26.0, 1337.0, 736.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 13.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 5.0, 5.0 ],
						"gridsnaponopen" : 0,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 44.382671,
									"frgb" : 0.0,
									"id" : "obj-16",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 7.0, 5.0, 205.0, 56.0 ],
									"text" : "faustgen~"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"id" : "obj-14",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 7.0, 61.0, 250.0, 20.0 ],
									"text" : "Faust as a Max/MSP external : version 1.12"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-29",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 431.0, 344.0, 256.0, 25.0 ],
									"text" : "a example to mute without click"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-27",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 106.0, 429.5, 256.0, 25.0 ],
									"text" : "a toggle switch off without click example"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-65",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 6,
											"minor" : 1,
											"revision" : 9,
											"architecture" : "x64"
										}
,
										"rect" : [ 25.0, 69.0, 640.0, 480.0 ],
										"bglocked" : 0,
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 15.0, 15.0 ],
										"gridsnaponopen" : 0,
										"statusbarvisible" : 2,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"description" : "",
										"digest" : "",
										"tags" : "",
										"boxes" : [ 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-31",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 131.0, 126.0, 100.0, 21.0 ],
													"text" : "abs~"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-29",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 50.0, 152.5, 100.0, 21.0 ],
													"text" : "gate~"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-28",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 131.0, 100.0, 100.0, 21.0 ],
													"text" : "rand~ 6"
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-63",
													"maxclass" : "inlet",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"patching_rect" : [ 50.0, 40.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-64",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 50.0, 233.5, 25.0, 25.0 ]
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"destination" : [ "obj-31", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-28", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-64", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-29", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-29", 1 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-31", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-29", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-63", 0 ]
												}

											}
 ]
									}
,
									"patching_rect" : [ 457.0, 238.0, 34.0, 21.0 ],
									"saved_object_attributes" : 									{
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0,
										"description" : "",
										"digest" : "",
										"fontface" : 0,
										"fontname" : "Arial",
										"fontsize" : 12.0,
										"globalpatchername" : "",
										"tags" : ""
									}
,
									"text" : "p"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-62",
									"maxclass" : "toggle",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 54.0, 431.5, 20.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-58",
									"maxclass" : "live.meter~",
									"numinlets" : 1,
									"numoutlets" : 1,
									"orientation" : 1,
									"outlettype" : [ "list" ],
									"patching_rect" : [ 34.0, 511.5, 100.0, 5.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-59",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 54.0, 458.5, 60.0, 19.0 ],
									"text" : "gain $1"
								}

							}
, 							{
								"box" : 								{
									"bitcode" : "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",
									"bitcode_size" : 8640,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-60",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 34.0, 485.0, 100.0, 21.0 ],
									"serial_number" : "C02JV2K0DKQ464 bits",
									"sourcecode" : "import(\"stdfaust.lib\"); \n \nprocess = *(gain)\r\n\twith{\r\n\t\tgain = vslider(\"gain\",0,0,1,1):si.smooth(0.99);\r\n\t\t};",
									"sourcecode_size" : 241,
									"text" : "faustgen~",
									"varname" : "faustgen-fc266d0",
									"version" : "1.12"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-57",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 34.0, 314.0, 100.0, 21.0 ],
									"text" : "loadmess 1",
									"varname" : "faustgen-1700dc8[2]"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-56",
									"maxclass" : "live.meter~",
									"numinlets" : 1,
									"numoutlets" : 1,
									"orientation" : 1,
									"outlettype" : [ "list" ],
									"patching_rect" : [ 439.0, 549.0, 100.0, 5.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-55",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "float", "int" ],
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 6,
											"minor" : 1,
											"revision" : 9,
											"architecture" : "x64"
										}
,
										"rect" : [ 25.0, 69.0, 358.0, 258.0 ],
										"bglocked" : 0,
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 15.0, 15.0 ],
										"gridsnaponopen" : 0,
										"statusbarvisible" : 2,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"description" : "",
										"digest" : "",
										"tags" : "",
										"boxes" : [ 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-2",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 165.0, 115.5, 60.0, 21.0 ],
													"text" : "pipe 40",
													"varname" : "faustgen-1700dc8[1]"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-3",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 3,
													"outlettype" : [ "int", "int", "stop" ],
													"patching_rect" : [ 165.0, 70.5, 131.0, 21.0 ],
													"text" : "t 1 0 stop",
													"varname" : "faustgen-1700dc8[6]"
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-1",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 80.0, 208.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-50",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "" ],
													"patching_rect" : [ 21.0, 115.5, 60.0, 21.0 ],
													"text" : "pipe 40",
													"varname" : "faustgen-1700dc8[5]"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-49",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 3,
													"outlettype" : [ "int", "int", "stop" ],
													"patching_rect" : [ 21.0, 70.5, 137.0, 21.0 ],
													"text" : "t 1 0 stop",
													"varname" : "faustgen-1700dc8[4]"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-48",
													"maxclass" : "newobj",
													"numinlets" : 3,
													"numoutlets" : 3,
													"outlettype" : [ "bang", "bang", "" ],
													"patching_rect" : [ 21.0, 43.0, 307.0, 21.0 ],
													"text" : "sel 0 1",
													"varname" : "faustgen-1700dc8[3]"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 13.0,
													"id" : "obj-27",
													"maxclass" : "newobj",
													"numinlets" : 2,
													"numoutlets" : 1,
													"outlettype" : [ "float" ],
													"patching_rect" : [ 21.0, 172.0, 30.0, 21.0 ],
													"text" : "f",
													"varname" : "faustgen-1700dc8[2]"
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-51",
													"maxclass" : "inlet",
													"numinlets" : 0,
													"numoutlets" : 1,
													"outlettype" : [ "int" ],
													"patching_rect" : [ 21.0, 0.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-52",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 21.0, 208.0, 25.0, 25.0 ]
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"destination" : [ "obj-1", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 174.5, 150.25, 89.5, 150.25 ],
													"source" : [ "obj-2", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-52", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-27", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-2", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-3", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-27", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 230.5, 164.75, 30.5, 164.75 ],
													"source" : [ "obj-3", 1 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-50", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 286.5, 109.0, 30.5, 109.0 ],
													"source" : [ "obj-3", 2 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-3", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-48", 1 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-49", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-48", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-1", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-49", 1 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-2", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"midpoints" : [ 148.5, 103.0, 174.5, 103.0 ],
													"source" : [ "obj-49", 2 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-50", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-49", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-27", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-50", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-48", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-51", 0 ]
												}

											}
 ]
									}
,
									"patching_rect" : [ 380.0, 373.5, 78.0, 21.0 ],
									"saved_object_attributes" : 									{
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0,
										"description" : "",
										"digest" : "",
										"fontface" : 0,
										"fontname" : "Arial",
										"fontsize" : 12.0,
										"globalpatchername" : "",
										"tags" : ""
									}
,
									"text" : "p"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-42",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 546.0, 446.5, 150.0, 40.0 ],
									"text" : "DSP to be muted, and listen to the click"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-43",
									"maxclass" : "toggle",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 439.0, 404.0, 20.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 1.0, 0.435746, 0.304679, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-44",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 439.0, 430.0, 54.0, 18.0 ],
									"text" : "mute $1"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-45",
									"maxclass" : "live.meter~",
									"numinlets" : 1,
									"numoutlets" : 1,
									"orientation" : 1,
									"outlettype" : [ "list" ],
									"patching_rect" : [ 439.0, 482.0, 100.0, 5.0 ]
								}

							}
, 							{
								"box" : 								{
									"bitcode" : "3sAXCwAAAAAUAAAAFBsAAAcAAAFCQ8DeIQwAAMIGAAALgiAAAgAAABIAAAAHgSORQcgESQYQMjmSAYQMJQUIGR4Ei2KAHEUCQpILQuQQMhQ4CBhJCjJEJEgKkCEjxFKADBkhciQHyMgRYqigqEDG8AEAAABRGAAAFAAAABuIIACWDYTw/////wMgbTCG/////x8ACaA2EAQAJBuMIgAWgNpgGAKwANUG4wiABag2GMj/////D4AEVBuQZAASYAGoDYhCAAmwABUAAAAASRgAAAgAAAAThECYIATDBIEQJgiFMUE4kAlCMUwIhgnBMYEIEkUAAIkgAABPAAAAMiLICSBkhQSTI6SEBJMj44ShkBQSTI6MC4TkTBCkwxwBkhIACiQLgAZZAaBCUgDokBoASmQLgBbZAaBGjgDokRsAiiQGgCYZAaBKEgDokhMAyiQCgDYJAaBOFgDokykACqUBgEbpAKBSNgDolA8ASqUFgFaZAaBWXgDoNQJAgCLEZDSbIwCDFKgNAaTA7R5piihh8gfpYbBBepBhw+FwtRvlihDT0W6OABSKIOuRrwQ6ApYhJpORkG6FiMlkRCoWJCaTEW+3242OxYjJZMTbjZKliMmIMhktr5GmiBIm3xXBhSJQIxsOhzSjEYlEKpVMapYhpnPSswg1HUXLUNPVaFqEWI2qZYjpanQtREwmk1H2HmmKKGHyTWICwIUikCDT0rYIMS51iViKmK72/RKYZDQkGtXmCALSTgEAABMyfMADO/gFO6CDNggHeIAHdiiHNiCHcJCHe0gHd4gDOXADO3ADONiAFuXQBvCgB3ZAB3pgB3SgB3ZAB20wC3EgB3jQBukQB3qAB3qAB22QDnigB3igB3jQBukQB3agB3FgB3oQB3bQBukwB3KgB3MgB3owB3LQBulgB3SgB3ZAB3pgB3TQBuYQB3agB3FgB3oQB3bQBuYwB3KgB3MgB3owB3LQBuZgB3SgB3ZAB3pgB3TQBuYQB3KAB3oQB3KAB3oQB3KAB21gD3ZAB3pgB3SgB3ZAB21gD3EgB3igB3EgB3igB3EgB3jQBuEAB3oAB3pgB3TQBvMAB3pgB3SgB3ZAB21gDngAB3oQB3KAB3oQB3KAB23gDnigB3FgB3owB3KgB3ZABzoPxEggI0REAAptYSCxFwYafWEgkhwGKtFhIDMdBjrVYSCUHQZK3WGg8BYGUuNhoFUeBkrfYSDWHgZq82EgVyQGekdioBQeBmr1YSAYJQYKcWGg8RcGavdhoJckBhrBYaAxHAaKW2Kglh8GglNioLckBpJdYqC2HwZa52EgshwGmmFiIFomBlrpYaAwFwYaxWGg1h8GglVioNckBjrXYaD2HwZi72GgtR4GIs1hoFAXBqpnYqA5JgYKd2EguyYGum1iIBwnBiLPYaD7JgbCc2IgeCUGCnlhILQdBhrHYSD5JQZqQWKg9yQGqmlioDYkBmLxYSCYJYYhCx0AARAIAAAAwJCFDwAAEAQAAABgyMIHAAAEAAAAADBk+QMgAAYAAAAAGLLwAQAAggAAAAAMWUIBAIABAAAAAIYssAAAACEAAAAAQxZZAACgAAAAAIAhiywAAGAAAAAAwJBFFgAAMAAAAABgyEILAAAYAAAAADBkoQUAAAwAAAAAGLLYAgAABwAAAAAMWXABAIAAAAAAAIYsvgAAAAIAAAAAQ5ZwAAAgAQAAAIAhCy4AABAAAAAAQBYILAEAADIemCAZEUyQjAkmR8YEQwpoVDaby2O6i50Wv8J1Ovot16iZpIKY6XHZPS+DUM0kNaWROc2ml+Uudlr8Ctfp6Ldco3YY357DXey0+BWu09FvuUbt+jw9drHT4hc7PS6752WN2vV5euxip8Uve1k+T7/dGsnL5Pq47GKnxa9wnY5+y2mga6Css9P1OejpAk3baToahFK/56AwHTQey9th15wedpvfcrKrTK6nqKBU2Wwuj+kudlr8Gr/heXn6jKYrZU6z6WW5i50Wv8ZveF6ePqPpShnD9TkdZEyz6WU5iJkWy8PyvFLmNJtelrvYafFLXjaX5WX3uKxUO4xvz+Eudlr8Gr/heXn6jKYrJS+T6+Oyi50Wv8ZveF6ePqPpdNBJWWen63PQ0wWattN0NCiZTOrEPEKZoHuajgaV8eMynJ5+u3Vq1+fpsYudFr/Gb3henj6j6Tq95+M0mx2mv+Uudlr8cofbZUpoVjaby2O6i50Wv8r4cZpeln/DdTr6LaeFsgFUns6H3eswaIour8NyEAo+R5fXYfl3PJa3w645Pew2v+VkV5lcT1FDubLZXB7TXey0+FXGj9P0svw7fsPz8vQZTVeuGcY3p1DQ+N2Gh+lpcZqdpudBzLRYHpbn6aFiMHzD8/L0GU0HocYpkAwWm4Gg8nQ+7F6HQVN0eR2Wqxhkw2436Clnh+XlPAj1lrPD8nIeFKaDzvJwu+wyy1MUUa1sNpfHdBc7LX6V8eM0vSz/stPjsnteVq1sNpfHdBc7LX6V8eM0vSz/2svyefrtVs0Yrs/poGCdnH6DimZzeUwHMdNieViep4leZbO5PKa72Gnxq4wfp+ll+dcdbpepohAyLG+/3ekxqIgfp+lluULtMB3tYqfFL3Z6XHbPywq1w3S0i50Wv+xl+Tz9divUrs/TYxc7LX6F63T0W06XHWqf3qH26x1ov6aMSmWzuTymu9hp8YudHpfd87JKZbO5PKa72Gnxy16Wz9Nvt0rmNJtelrvYafGLnR6X3fOySuY0m16Wu9hp8ctels/Tb7dK7TAd7WKnxa/xG56Xp89oukrtML49h7vYafGLnR6X3fOySu0wvj2Hu9hp8ctels/Tb7dK8jK5Pi672Gnxi50el93zskryMrk+LrvYafHLXpbP0283bfSYUpctmmtGHX3KZnN5THex0+KXO9wu62NOs+lluYudFr/c4XZZn3aYjnax0+JXuE5Hv+X6tMP49hzuYqfFL3e4XdZHXibXx2UXOy1+ucPtMn2WqP37XqL27X6JEkzLJWq/rpegL5qmkKIBmk6Hz3Wv13gsb4ddc3rYbX7Lya4yuf7yq9/zlznNppfl8xeNtgBXzfS2ACOAIaikTTtMR7vYafHLHW6XtWnW5+kxiJkWy8PyPJ2UaYbpaBAzLZaH5XlKqdOuz9NjFzstfrnD7bI60jK5Pi6DmGmxPCzP00qr93ycZrPD9LfcxU6LX+E6Hf2WU0ux93ycZrPD9LfcxU6LX+M3PC9Pn9F0xYzh+pwOes7HaTY7TH/LQcy0WB6W5+ml1ns+TrPZYfpb7mKnxS92elx2z8tqvefjNJsdpr/lLnZa/LKX5fP02w0AAHkYAAAXAAAAMwiAHMThHGYUAT2IQziEw4xCgAd5eAdzmHEM5gAP7RAO9IAOMwxCHsLBHc6hHGYwBT2IQziEgxvMAz3IQz2MAz3MeIx0cAd7CAd5SIdwcAd6cAN2eIdwIAcAAABxIAAAZgEAAGa0DMRCTASDDdJjTZJBTCfFoNT0UJPEYIP0GBFRRARRA5Oyzk7X56CnCzRtp+loUDKZtAmi9u/bhgj6omlzigxiEpuHmlZgIhhskJ6iwd7zcZrNDtPfchc7LX6N3/C8PH1G082jAFfN9KynACOAIQrIkZbJ9XEZxEyL5WF53hqG2qeNZaj9ugLWQFlnp+tz0NMFmrbTdDQIpX7PQWE6aDyWt8OuOT3sNr/lZFeZXE8ZUgMsiyMAE8Fgg/RUjfWej9Nsdpj+lrvYafGLnR6X3fNyPRxT6rJFc80qpmnW5+kxiJkWy8PyvCUhDWEx2CA99SG1w3S0i50Wv8ZveF6ePqPpxaCVzebymO5ip8WvMn6cppflX3tZPk+/3WUzvefjNJsdpr/lLnZa/HKH2+UqYAOoPJ0Pu9dh0BRdXoflIBR8ji6vw/LveCxvh11zethtfsvJrjK5njKmyCCmk2LE5qEmicEG6SkQqB2mo13stPjFTo/L7nnZqBKkQSYGG6SnTKh2GN+ew13stPg1fsPz8vQZTa8FCBmWt9/u9BhUxI/T9LK8eCh5mVwfl13stPg1fsPz8vQZTa8Rphmmo0HMtFgelufr55GXyfVx2cVOi1/ucLtsSldAIcvgSkQkNhMRFYBAMNggPSbVMMQEDMAEMNggPeUjycvk+rjsYqfFL3Z6XHbPy3UgBsM3PC9Pn9F0EGqcAslgsRkIKk/nw+51GDRFl9dheXU87TAd7WKnxa9wnY5+y6uCMqfZ9LLcxU6LX+M3PC9Pn9H0usGM4fqcDnrOx2k2O0x/y0HMtFgelucLx3rPx2k2O0x/y13stPhlL8vn6bfbipiBkKbIwRhskJ56idr1eXrsYqfFL3Z6XHbPyxUyMY9QJuiepqNBZfy4DKen3+46kdphfHsOd7HT4hc7PS675+WykMxpNr0sd7HT4hc7PS675+UqidphfHsOd7HT4le4Tke/5ZZD1H5dl4NUNpvLY7qLnRa/2Olx2T0vFwnUDtPRLnZa/LKX5fP0210EWdlsLo/pLnZa/Crjx2l6Wf4N1+not7wSomaSCmKmx2X3vAxCNZPUlD1JBjGh1PRQ0wpMBIMN0lM7YpANu92gp5wdlpfzINRbzg7Ly3lQmA46y8PtssssTxVFZE6z6WW5i50Wv8J1OvotN6GB9utakdphfHsOd7HT4pe9LJ+n3+4KkuRlcn1cdrHT4pe9LJ+n3+6Ccdr1eXrsYqfFL3e4XS6ZqF2fp8cudlr8spfl8/TbXRpogKbT4XPd6zUey9th15wedpvfcrKrTK6//Or3/GVOs+ll+fxVGJQxXJ/TQcY0m16Wg5hpsTwsz5dI0w7T0S52Wvxyh9vl2pDMaTa9LHex0+KXvSyfp9/ugnjKZnN5THex0+KXO9wu10z1no/TbHaY/pa72GnxK1yno9/yUuGaYXxzCgWN3214mJ4Wp9lpeh7ETIvlYXm+JKSy2Vwe013stPhlL8vn6be7WqB2fZ4eu9hp8Stcp6Pf8sqgzGk2vSx3sdPil7xsLsvL7nHZOIjat/tKedphfHsOd7HT4pc73C6XAVc2m8tjuoudFr/K+HGaXpZ/x294Xp4+o+nlMrXr8/TYxU6LX+M3PC9Pn9F0QyFKMC1tihEc5qEmgsEG6SmAqGw2l8d0FzstfoXrdPRbXgpX2Wwuj+kudlr8KuPHaXpZ/nWH22WLipBGmoBGIMQGmRhskJ6K0Izh+pwOCtbJ6TeoaDaXx3QQMy2Wh+X5QtDKZnN5THex0+JXGT9O08vyLzs9LrvnZTsyGGBZHMGgHGEBJElskInBBumpi8ecZtPLchc7LX65w+2yLUkGMbEA8yzECkwEgw3SUwJU2Wwuj+kudlr8Gr/heXn6jKaXTiQvk+vjsoudFr/CdTr6LQcAAABhIAAACQAAABMEAYYDAQAABQAAAJYZMAzScwAL0UwR9geLIygAAAAAAAAAAGEgAAAJAAAAEwTBBbIdMSCA4BYCDAcCAAMAAAAHUBDNFGGWGTAM0gMAAAAAYSAAAAkAAAATBAGGAwEAAAUAAACWGTAM0nMAC9FMEfYHiyMoAAAAAAAAAABhIAAADQAAABMEQSwQAAAAAgAAANQrwAQAAAAAIwYEEMxCcIFuMwgHAgAAAAIAAAAHUBDNFGEAAAAAAABhIAAAGQAAABMEQSwQAAAABgAAANQbAaDaCEAZFALJhjLAYBTqgCfqgCcAAGeIlwIw3oAcBQVgxKAAgmAoxhuUxKAAjBgQQBAUGA4EBgAAAKYZkCDNREQFIBAHQCANMllmwDBIDwAAAAAAAABhIAAADwAAABMEQSwQAAAAAgAAAFQbASgEAAAA4w2DEFAAMggHAgAABQAAAJYZMAzScwAL0UwR9geLIygAAAAAAAAAAGEgAAAMAAAAEwRBLBAAAAABAAAAVBsBABmEAwEFAAAAlhkwDNJzAAvRTBH2B4sjKAAAAAAAAAAAYSAAAAwAAAATBEEsEAAAAAEAAABUKwEAGYQDAQUAAACWGTAM0nMAC9FMEfYHiyMoAAAAAAAAAABhIAAADgAAABMEQSwQAAAAAQAAAFSrAQAZhAMBBwAAAJYZMAzSY5oBh3AATUMsB7AQzRRhf7A4ggIAAAAAAAAAYSAAABQAAAATBEEsEAAAAAIAAABUGwEogRoAAMMNxAAG0w2DEGQQDgQAAAAJAAAA5hlACE4zWGbAMEiPaQYcwgE0DbEcwEI0U4T9weIIin0GBD4AAAAAAGEgAAAKAAAAEwQBhgMBAAAGAAAAlhnASADzLEhjfBEBHcBCNFOE/cHiCAoAAAAAAGEgAAA6AAAAEwRBLBAAAAAMAAAAVBsBKIEiKINCKEDci1Kg3ggA3cYI9hxWezaOxZ4HiTEC29fvOz9717b9YQQAAAAA4w3NcgxGBA0AnFPewYigAYDxiMdomMGIwAEAGsBwQ+CgwXTDIwTDDQFjBifcrJaAphuWYBhvuKpnMCIQAGA8AnsqazAiaABgPCKDLGswInAAYDxCiyxsMCJ4AGA8YpMubDAigABgPIKbLm0wIogAYDyiozBtMCKQAADDgQAAAAAJAAAAlhkwDNJjmgGMBDDPgjTGFxHQASxEM0XYHyyOoJhrwOA7DwAAAAAAAGEgAAAMAQAAEwRBLBAAAACsAAAA1BsBoFoJjACQbCgDa+qAJ+qAJ4YyuKcOeKIOeGIoAwmDOuCJOuCJoQwwQIM64Ik64ImhDAGoA56oA54YyjCEOuCJOuCJoQyFqAOeqAOeGMpgijrgiTrgiaEMx6gDnqgDnhjKgI464Ik64ImhDAmpA56oA54YyhCSOuCJOuCJoQxKqQOeqAOeGMqwljrgiTrgiaEMiakDnqgDnhjK0Jw64Ik64ImhDA+qA56oA54YypCiOuCJOuCJoQxNqgOeqAOeGMoAg6kOeKIOeGIoQ6DqgCfqgCeGMoyqDniiDnhiKEOz6oAn6oAnhjK8qw54og54YijDwOqAJ+qAJ4YyjKwOeKIOeGIoQwy0OuCJOuCJoQxtqwOeqAOeGMoAA64OeKIOeGIow+vqgCfqgCeGMrSvDniiDnhiKMMCgzrgiTrgiaEMMxCDOuCJOuCJoQw0GIM64Ik64ImhDIsM6oAn6oAnhjKEMqgDnqgDnhjKMMygDniiDnhiKEM7gzrgiTrgiaEMLw3qgCfqgCeGMhw1qAOeqAOeGMrQ1qAOeKIOeGIoA2ODOuCJOuCJoQyrDeqAJ+qAJ4YyEDeoA56oA54YyhDeoA54og54YihDDeCgDniiDnhiKMMM4qAOeKIOeGIoQ5CDOuCJOuCJoQw2mIM64Ik64ImhDDeggzrgiTrgiaEMOKiDOuCJOuCJoQzEDuqAJ+qAJ4Yy3OAO6oAn6oAnhjLgAA/qgCfqgCeGMsAgD+qAJ+qAJ4YyBD2oA56oA54YyoD2oA54og54YijD4IM64Ik64ImhDDLogzrgiTrgiaEMzQ/qgCfqgCeGMrw/qAOeqAOeGMpQA1CoA56oA54YytBCoQ54og54YigDE4U64Ik64ImhDGSoA56oA54YyiCCOuCJOuCJoQwy8OqAJ+qAJwAAAHcK4qUADDGkAiqcAgVgxMAAgmAYBWPEwACCYBCFY8TAAIJgCAVQGDEwgCAY/sAPRgwMIAiGPuCDEQMDCIJhD/RgxMAAgmDIg1MYMTCAIBjwwBRGDAwgCIY7sIMRAwMIgqEO6GDEwACCYJgDY8TAAIJgkINjxMAAgmCIA1MYMTCAIBjg4A1GDAwgCAY3aIMRAwMIgoEN1mDEwACCYFCDYsTAAIJgSINixMAAgmBAg1IYMTCAIBjOwAxGDAwgCIYyOIURAwMIgoEMihEDAwiCYQyKEQMDCIJBDEhhxMAAgmAIAzAYMTCAIBg+b8TAAIJg6IoRAwMIgoErRgwMIAiGrRRGDAwgCAYtGzEwgCAYsFMYMTCAIBguY8TAAIJgsI4RAwMIgqEyhREDAwiCgZpGDAwgCAYpGjEwgCAYoGfEwACCYHCaEQMDCIKBIYURAwMIgmFRRgwMIAiGBMFwIAQAAAAHsBDNFGF/sDiCYpkBAQMAAAAAAGEgAAClAAAAEwRELBAAAAAMAAAAVBsBKIEaoF4JFFSBFGBAgRVEARVCwdBtjAAEQRAEQRAE8X8YIwBBEARBEARB/h8Aww2RYwazDMEQEARmCYSBijroBcEMgoEKUsgFgQjOKu9gRCABwF29rOCBC4hKAbitlxVIcAFRKQD39bKCCi4gKgXAikA+pQRxZdDLCjS4gKiDEQEBAIcGvayAgwuISgGgB1iQyMeGAD4WePA5OOhlBWMAF5SVAnDBzcwI4nN20MsK0AAuIOpgREAAwOVBLyuQA7iAqIMRwQEAdrCBfAYj0CAAADoDMBjBBABAFxiMMIMAAOgAgxFWAABUgMEIMAgAYAiBDfSg3IAPYLgh+AMwmGUYhADDgQAAXgAAABYcoEhUowDDENm0CQcoEtUowDBEdm2bAQbSPNQkGWfA4VDTQ02SJQcoEtUowDBENm7DAYpENQowDJF923KAIlGNAgxDZO+mGVAIDtVMphygSFSjAMMQ2bo9BygS1SjAMEQ2b9ABikQ1CjAMkd0bbEAiUY0CDENkW2xAIlGNAgxDdJtsQCJRjQIMQ5QbbUAiUY0CDEOkW21AIlGNAgxDxF9AJTgD8QeLIyi2/0TEQQADEZltQCJRjQIMQ9QfwEI0U4T9weIIiuEGKBLVKMAwRHVtuQGKRDUKMAxRbZtugCJRjQIMQ1Tj5hugSFSjAMMQ1fkNGBExUVFjvwGKRDUKMAxRvVtmwDBIjwEHKBLVKMAwRDVv0QGKRDUKMAzRTZt0gCJRjQIMQ3TXth2wLFLkI5XfENdk2gGHJBCVQTzWGnAsUuQjVW3TAYpENQowDNFtG3WAIlGNAgxDdN8nsAjOQPzB4giKba4BxiJFPlIZdwBCXMgkOM0AAAAAAAAAYSAAADoAAAATBEEsEAAAAAwAAABUGwEogSIog0IoQNyLUqDeCADdxgj2HFZ7No7FngeJMQLb1+87P3vXtv1hBAAAAADjDc1yDEYEDQCcU97BiKABgPGIx2iYwYjAAQAawHBD4KDBdMMjBMMNAWMGJ9ysloCmG5ZgGG+4qmcwIhAAYDwCeyprMCJoAGA8IoMsazAicABgPEKLLGwwIngAYDxiky5sMCKAAGA8gpsubTAiiABgPKKjMG0wIpAAAMOBAAAAAAkAAADmGlD4zuMjlhkwDNJjmgGMBDDPgjTGFxHQASxEM0XYHyyOoAAAAAAAAAAAAAAAAAAAAAAA",
									"bitcode_size" : 9280,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-46",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 439.0, 456.0, 100.0, 21.0 ],
									"serial_number" : "C02JV2K0DKQ464 bits",
									"sourcecode" : "import(\"stdfaust.lib\"); \n \nprocess = os.oscs(50):*(0.5);",
									"sourcecode_size" : 189,
									"text" : "faustgen~",
									"varname" : "faustgen-c42dda0",
									"version" : "1.12"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-32",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 380.0, 495.5, 60.0, 19.0 ],
									"text" : "gain $1"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-26",
									"maxclass" : "toggle",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 380.0, 346.0, 20.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"bitcode" : "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",
									"bitcode_size" : 8640,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-23",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 439.0, 522.5, 100.0, 21.0 ],
									"serial_number" : "C02JV2K0DKQ464 bits",
									"sourcecode" : "import(\"stdfaust.lib\"); \n \nprocess = *(gain)\r\n\twith{\r\n\t\tgain = vslider(\"gain\",0,0,1,1):si.smooth(0.99);\r\n\t\t};",
									"sourcecode_size" : 241,
									"text" : "faustgen~",
									"varname" : "faustgen-c48fbd0",
									"version" : "1.12"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-21",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 380.0, 316.5, 100.0, 21.0 ],
									"text" : "loadmess 1",
									"varname" : "faustgen-1700dc8"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-40",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 88.0, 334.5, 157.0, 40.0 ],
									"text" : "DSP to be muted, and listen to the click"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-54",
									"maxclass" : "toggle",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 34.0, 344.5, 20.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 1.0, 0.435746, 0.304679, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-53",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 34.0, 370.5, 54.0, 18.0 ],
									"text" : "mute $1"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-15",
									"maxclass" : "live.meter~",
									"numinlets" : 1,
									"numoutlets" : 1,
									"orientation" : 1,
									"outlettype" : [ "list" ],
									"patching_rect" : [ 34.0, 422.5, 100.0, 5.0 ]
								}

							}
, 							{
								"box" : 								{
									"bitcode" : "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",
									"bitcode_size" : 9280,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-5",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 34.0, 396.5, 100.0, 21.0 ],
									"serial_number" : "C02JV2K0DKQ464 bits",
									"sourcecode" : "import(\"stdfaust.lib\"); \n \nprocess = os.oscs(50):*(0.5);",
									"sourcecode_size" : 189,
									"text" : "faustgen~",
									"varname" : "faustgen-c49abb0",
									"version" : "1.12"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-9",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 27.0, 157.0, 464.0, 25.0 ],
									"text" : "be carefull with you level control, this demo uses a low frequency oscillator"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-30",
									"maxclass" : "toggle",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 457.0, 207.0, 20.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-22",
									"maxclass" : "live.meter~",
									"numinlets" : 1,
									"numoutlets" : 1,
									"orientation" : 1,
									"outlettype" : [ "list" ],
									"patching_rect" : [ 457.0, 288.5, 100.0, 5.0 ]
								}

							}
, 							{
								"box" : 								{
									"bitcode" : "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",
									"bitcode_size" : 9344,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-24",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 457.0, 260.5, 100.0, 21.0 ],
									"serial_number" : "C02JV2K0DKQ464 bits",
									"sourcecode" : "import(\"stdfaust.lib\"); \n \nprocess = _,os.oscs(50):*;",
									"sourcecode_size" : 185,
									"text" : "faustgen~",
									"varname" : "faustgen-c4b14f0",
									"version" : "1.12"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-25",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 503.0, 197.0, 193.0, 40.0 ],
									"text" : "or use directly a audio input to control gain"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-13",
									"maxclass" : "flonum",
									"maximum" : 1.0,
									"minimum" : 0.0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "float", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 262.0, 207.0, 50.0, 21.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-18",
									"maxclass" : "live.meter~",
									"numinlets" : 1,
									"numoutlets" : 1,
									"orientation" : 1,
									"outlettype" : [ "list" ],
									"patching_rect" : [ 262.0, 288.5, 100.0, 5.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-19",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 262.0, 235.0, 60.0, 19.0 ],
									"text" : "gain $1"
								}

							}
, 							{
								"box" : 								{
									"bitcode" : "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",
									"bitcode_size" : 9664,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-20",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 262.0, 260.5, 100.0, 21.0 ],
									"serial_number" : "C02JV2K0DKQ464 bits",
									"sourcecode" : "import(\"stdfaust.lib\"); \n \nprocess = os.oscs(50):*(gain)\r\n\twith{\r\n\t\tgain = vslider(\"gain\",0,0,1,0.001):si.smooth(0.99);\r\n\t\t};",
									"sourcecode_size" : 255,
									"text" : "faustgen~",
									"varname" : "faustgen-128037e0",
									"version" : "1.12"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-11",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 339.0, 197.0, 112.0, 40.0 ],
									"text" : " with a Faust smooth filter"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-7",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 83.0, 188.0, 178.0, 54.0 ],
									"text" : "continuously change this gain to listen artefact without smooth filter"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-4",
									"maxclass" : "flonum",
									"maximum" : 1.0,
									"minimum" : 0.0,
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "float", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 7.0, 205.0, 50.0, 21.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-33",
									"local" : 1,
									"maxclass" : "ezdac~",
									"numinlets" : 2,
									"numoutlets" : 0,
									"ongradcolor1" : [ 0.992157, 0.714953, 0.066136, 1.0 ],
									"patching_rect" : [ 7.0, 674.5, 45.0, 45.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-38",
									"maxclass" : "live.gain~",
									"numinlets" : 2,
									"numoutlets" : 5,
									"outlettype" : [ "signal", "signal", "", "float", "list" ],
									"parameter_enable" : 1,
									"patching_rect" : [ 7.0, 563.0, 54.0, 102.0 ],
									"saved_attribute_attributes" : 									{
										"valueof" : 										{
											"parameter_longname" : "live.gain~[9]",
											"parameter_shortname" : "live.gain~",
											"parameter_type" : 0,
											"parameter_mmin" : -70.0,
											"parameter_mmax" : 6.0,
											"parameter_initial_enable" : 1,
											"parameter_initial" : [ -20 ],
											"parameter_unitstyle" : 4
										}

									}
,
									"varname" : "live.gain~"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-17",
									"maxclass" : "live.meter~",
									"numinlets" : 1,
									"numoutlets" : 1,
									"orientation" : 1,
									"outlettype" : [ "list" ],
									"patching_rect" : [ 7.0, 286.5, 100.0, 5.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-2",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 7.0, 233.0, 60.0, 19.0 ],
									"text" : "gain $1"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"bubbleside" : 2,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-6",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 34.0, 88.0, 461.0, 69.0 ],
									"text" : "A smooth filter function included in Faust libraries is very usefull to use when you want to drive continuous parameters from Max to Faust and reduce audio artefacts from interruptions..."
								}

							}
, 							{
								"box" : 								{
									"bitcode" : "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",
									"bitcode_size" : 9408,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-1",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 7.0, 258.5, 100.0, 21.0 ],
									"serial_number" : "C02JV2K0DKQ464 bits",
									"sourcecode" : "import(\"stdfaust.lib\"); \n \nprocess = os.oscs(50):*(gain)\r\n\twith{\r\n\t\tgain = vslider(\"gain\",0,0,1,0.001);\r\n\t\t};",
									"sourcecode_size" : 243,
									"text" : "faustgen~",
									"varname" : "faustgen-128e7f40",
									"version" : "1.12"
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-66",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 60.0, 344.5, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "5",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-28",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 80.0, 431.5, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "6",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-34",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 405.0, 346.0, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "7",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-10",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 7.0, 159.5, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "1",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-12",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 479.0, 207.0, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "4",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-8",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 315.0, 207.0, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "3",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-3",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 60.0, 205.0, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "2",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-17", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-38", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-13", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-20", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-19", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-1", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-2", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-18", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-20", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-38", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 271.5, 297.75, 16.5, 297.75 ],
									"source" : [ "obj-20", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-26", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-21", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-38", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 448.5, 552.75, 16.5, 552.75 ],
									"source" : [ "obj-23", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-56", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-23", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-24", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-38", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 466.5, 297.75, 16.5, 297.75 ],
									"source" : [ "obj-24", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-55", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-26", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-65", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-30", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 389.5, 518.0, 448.5, 518.0 ],
									"source" : [ "obj-32", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-33", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-38", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-33", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-38", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-2", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-44", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-43", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-46", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-44", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-23", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-46", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-45", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-46", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-15", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-60", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-53", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-53", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-54", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-55", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-43", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-55", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-54", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-57", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-62", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-57", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-60", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 63.5, 480.5, 43.5, 480.5 ],
									"source" : [ "obj-59", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-38", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 43.5, 523.0, 16.5, 523.0 ],
									"source" : [ "obj-60", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-58", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-60", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-59", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-62", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-24", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-65", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 10.0, 129.0, 62.0, 20.0 ],
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 13.0,
						"description" : "",
						"digest" : "",
						"fontface" : 0,
						"fontname" : "Arial",
						"fontsize" : 13.0,
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p smooth",
					"varname" : "basic_tab[5]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-6",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 1,
							"revision" : 9,
							"architecture" : "x64"
						}
,
						"rect" : [ 0.0, 26.0, 1337.0, 736.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 13.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 5.0, 5.0 ],
						"gridsnaponopen" : 0,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-1",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 91.0, 637.5, 452.0, 25.0 ],
									"text" : "switch on this dac and test messages..."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 44.382671,
									"frgb" : 0.0,
									"id" : "obj-16",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 7.0, 5.0, 205.0, 56.0 ],
									"text" : "faustgen~"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"id" : "obj-14",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 7.0, 61.0, 250.0, 20.0 ],
									"text" : "Faust as a Max/MSP external : version 1.12"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-3",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 20,
									"outlettype" : [ "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal", "signal" ],
									"patcher" : 									{
										"fileversion" : 1,
										"appversion" : 										{
											"major" : 6,
											"minor" : 1,
											"revision" : 9,
											"architecture" : "x64"
										}
,
										"rect" : [ 25.0, 69.0, 1542.0, 210.0 ],
										"bglocked" : 0,
										"openinpresentation" : 0,
										"default_fontsize" : 12.0,
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"gridonopen" : 0,
										"gridsize" : [ 15.0, 15.0 ],
										"gridsnaponopen" : 0,
										"statusbarvisible" : 2,
										"toolbarvisible" : 1,
										"boxanimatetime" : 200,
										"imprint" : 0,
										"enablehscroll" : 1,
										"enablevscroll" : 1,
										"devicewidth" : 0.0,
										"description" : "",
										"digest" : "",
										"tags" : "",
										"boxes" : [ 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-47",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 1434.0, 119.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-48",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 1359.0, 119.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-49",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 1283.0, 119.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-50",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 1213.0, 119.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-39",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 1149.0, 119.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-40",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 1074.0, 119.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-41",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 998.0, 119.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-42",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 928.0, 119.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-43",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 854.0, 119.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-44",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 779.0, 119.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-45",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 703.0, 119.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-46",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 633.0, 119.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-35",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 554.0, 119.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-36",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 479.0, 119.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-37",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 403.0, 119.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-38",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 333.0, 119.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-34",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 259.0, 119.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-33",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 184.0, 119.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-32",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 108.0, 119.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"comment" : "",
													"id" : "obj-31",
													"maxclass" : "outlet",
													"numinlets" : 1,
													"numoutlets" : 0,
													"patching_rect" : [ 38.0, 119.0, 25.0, 25.0 ]
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-30",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 1434.0, 78.0, 55.0, 20.0 ],
													"text" : "rand~ 6."
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-29",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 1359.0, 78.0, 62.0, 20.0 ],
													"text" : "rand~ 5.5"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-28",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 1283.0, 78.0, 55.0, 20.0 ],
													"text" : "rand~ 5."
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-27",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 1213.0, 78.0, 62.0, 20.0 ],
													"text" : "rand~ 4.5"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-26",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 1149.0, 78.0, 55.0, 20.0 ],
													"text" : "rand~ 4."
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-25",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 1074.0, 78.0, 62.0, 20.0 ],
													"text" : "rand~ 3.5"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-24",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 998.0, 78.0, 55.0, 20.0 ],
													"text" : "rand~ 3."
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-23",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 928.0, 78.0, 62.0, 20.0 ],
													"text" : "rand~ 2.5"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-22",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 854.0, 78.0, 55.0, 20.0 ],
													"text" : "rand~ 2."
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-21",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 779.0, 78.0, 62.0, 20.0 ],
													"text" : "rand~ 1.5"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-20",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 703.0, 78.0, 55.0, 20.0 ],
													"text" : "rand~ 1."
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-18",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 38.0, 78.0, 62.0, 20.0 ],
													"text" : "rand~ 0.1"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-6",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 633.0, 78.0, 62.0, 20.0 ],
													"text" : "rand~ 0.9"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-7",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 554.0, 78.0, 62.0, 20.0 ],
													"text" : "rand~ 0.8"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-8",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 479.0, 78.0, 62.0, 20.0 ],
													"text" : "rand~ 0.7"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-9",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 403.0, 78.0, 62.0, 20.0 ],
													"text" : "rand~ 0.6"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-5",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 333.0, 78.0, 62.0, 20.0 ],
													"text" : "rand~ 0.5"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-4",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 259.0, 78.0, 62.0, 20.0 ],
													"text" : "rand~ 0.4"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-3",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 184.0, 78.0, 62.0, 20.0 ],
													"text" : "rand~ 0.3"
												}

											}
, 											{
												"box" : 												{
													"fontname" : "Arial",
													"fontsize" : 12.0,
													"id" : "obj-1",
													"maxclass" : "newobj",
													"numinlets" : 1,
													"numoutlets" : 1,
													"outlettype" : [ "signal" ],
													"patching_rect" : [ 108.0, 78.0, 62.0, 20.0 ],
													"text" : "rand~ 0.2"
												}

											}
 ],
										"lines" : [ 											{
												"patchline" : 												{
													"destination" : [ "obj-32", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-1", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-31", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-18", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-45", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-20", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-44", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-21", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-43", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-22", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-42", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-23", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-41", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-24", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-40", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-25", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-39", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-26", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-50", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-27", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-49", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-28", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-48", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-29", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-33", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-3", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-47", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-30", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-34", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-4", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-38", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-5", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-46", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-6", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-35", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-7", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-36", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-8", 0 ]
												}

											}
, 											{
												"patchline" : 												{
													"destination" : [ "obj-37", 0 ],
													"disabled" : 0,
													"hidden" : 0,
													"source" : [ "obj-9", 0 ]
												}

											}
 ]
									}
,
									"patching_rect" : [ 36.25, 450.0, 415.0, 20.0 ],
									"saved_object_attributes" : 									{
										"default_fontface" : 0,
										"default_fontname" : "Arial",
										"default_fontsize" : 12.0,
										"description" : "",
										"digest" : "",
										"fontface" : 0,
										"fontname" : "Arial",
										"fontsize" : 12.0,
										"globalpatchername" : "",
										"tags" : ""
									}
,
									"text" : "p rand~"
								}

							}
, 							{
								"box" : 								{
									"bitcode" : "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",
									"bitcode_size" : 27372,
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-4",
									"maxclass" : "newobj",
									"numinlets" : 21,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 15.25, 482.5, 436.0, 20.0 ],
									"serial_number" : "C02JV2K0DKQ464 bits",
									"sourcecode" : "import(\"stdfaust.lib\"); \r\n\r\n// Example programmed by Christophe Lebreton - GRAME\n \nf(i) = hslider(\"freq%3i\", 160.,-0.,20000.,0.001);\nr(i) = hslider(\"decay%3i\", 0.,0.,1.,0.001):((pow(4.78)*6)+0.0001):ba.tau2pole;\n//g(i) = hslider(\"gain%3i\", 0.,0.,1.,0.0001);\n\n\n//resonator(n) = _<:par(i,n,*(g(i)) :fi.nlf2(f(i),r(i)):_,!:*(ba.db2linear((100*(log(1/r(i))))))):>*(0.003162);\n\r\nresonator(n) = (_ <: par(i, n, _)), si.bus(n) : ro.interleave(n,2) : par(i,n,*) : par(i,n,fi.nlf2(f(i),r(i)):_,!:*(ba.db2linear((100*(log(1/r(i))))))):>*(0.003162);\n\n\nprocess = resonator(20);",
									"sourcecode_size" : 682,
									"text" : "faustgen~",
									"varname" : "faustgen-129d50f0",
									"version" : "1.12"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-50",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 458.25, 472.5, 203.0, 40.0 ],
									"text" : "compare code and SVG with \"messages_inputs\" TAB"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-40",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 98.25, 372.0, 108.0, 25.0 ],
									"text" : "mute the DSP"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"bubbleside" : 2,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-36",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 7.0, 91.0, 481.0, 40.0 ],
									"text" : "It's the same example of \"messages\" Tab but with signal inputs to control gains"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-33",
									"local" : 1,
									"maxclass" : "ezdac~",
									"numinlets" : 2,
									"numoutlets" : 0,
									"ongradcolor1" : [ 0.992157, 0.714953, 0.066136, 1.0 ],
									"patching_rect" : [ 15.25, 627.0, 45.0, 45.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 24.331179,
									"frgb" : 0.0,
									"id" : "obj-25",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 135.25, 260.5, 97.0, 34.0 ],
									"text" : "DECAY"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-54",
									"maxclass" : "toggle",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 42.25, 349.5, 20.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 1.0, 0.435746, 0.304679, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-53",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 42.25, 375.5, 54.0, 18.0 ],
									"text" : "mute $1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 24.331179,
									"frgb" : 0.0,
									"id" : "obj-34",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 145.25, 144.0, 77.0, 34.0 ],
									"text" : "FREQ"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 1.0, 0.717647, 0.984314, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-11",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 49.25, 212.5, 100.0, 20.0 ],
									"text" : "prepend \"freq  0\""
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 1.0, 0.717647, 0.984314, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-9",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 49.25, 312.5, 112.0, 20.0 ],
									"text" : "prepend \"decay  0\""
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.8, 0.8, 0.8, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-65",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 28.75, 412.0, 40.0, 20.0 ],
									"text" : "pink~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
									"candicane2" : [ 0.145098, 0.203922, 0.356863, 1.0 ],
									"candicane3" : [ 0.290196, 0.411765, 0.713726, 1.0 ],
									"candicane4" : [ 0.439216, 0.619608, 0.070588, 1.0 ],
									"candicane5" : [ 0.584314, 0.827451, 0.431373, 1.0 ],
									"candicane6" : [ 0.733333, 0.035294, 0.788235, 1.0 ],
									"candicane7" : [ 0.878431, 0.243137, 0.145098, 1.0 ],
									"candicane8" : [ 0.027451, 0.447059, 0.501961, 1.0 ],
									"candycane" : 4,
									"contdata" : 1,
									"id" : "obj-8",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 49.25, 247.0, 269.0, 61.0 ],
									"peakcolor" : [ 0.498039, 0.498039, 0.498039, 1.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 416.0, 56.0, 196.0, 118.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"setstyle" : 1,
									"size" : 20,
									"slidercolor" : [ 0.890196, 0.647059, 0.992157, 1.0 ],
									"varname" : "Reson-Decay"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
									"candicane2" : [ 0.145098, 0.203922, 0.356863, 1.0 ],
									"candicane3" : [ 0.290196, 0.411765, 0.713726, 1.0 ],
									"candicane4" : [ 0.439216, 0.619608, 0.070588, 1.0 ],
									"candicane5" : [ 0.584314, 0.827451, 0.431373, 1.0 ],
									"candicane6" : [ 0.733333, 0.035294, 0.788235, 1.0 ],
									"candicane7" : [ 0.878431, 0.243137, 0.145098, 1.0 ],
									"candicane8" : [ 0.027451, 0.447059, 0.501961, 1.0 ],
									"candycane" : 4,
									"contdata" : 1,
									"id" : "obj-17",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 49.25, 137.0, 269.0, 60.0 ],
									"peakcolor" : [ 0.498039, 0.498039, 0.498039, 1.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 175.0, 57.0, 196.0, 118.0 ],
									"setminmax" : [ 20.0, 3000.0 ],
									"setstyle" : 1,
									"size" : 20,
									"slidercolor" : [ 0.890196, 0.647059, 0.992157, 1.0 ],
									"varname" : "Reson-Freq"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hidden" : 1,
									"id" : "obj-23",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 214.0, 7.0, 59.5, 20.0 ],
									"restore" : 									{
										"Reson-Decay" : [ 0.135593, 0.711864, 0.711864, 0.711864, 0.711864, 0.711864, 0.576271, 0.542373, 0.694915, 0.711864, 0.559322, 0.627119, 0.661017, 0.661017, 0.644068, 0.542373, 0.491525, 0.491525, 0.491525, 0.016949 ],
										"Reson-Freq" : [ 1407.241333, 1510.0, 1510.0, 1510.0, 1150.344849, 1150.344849, 1150.344849, 1150.344849, 1150.344849, 1150.344849, 1098.965576, 1098.965576, 1098.965576, 1098.965576, 944.827576, 944.827576, 996.206909, 996.206909, 1612.758667, 1510.0 ],
										"live.gain~" : [ -20.001749 ]
									}
,
									"text" : "autopattr",
									"varname" : "u781000125"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-38",
									"maxclass" : "live.gain~",
									"numinlets" : 2,
									"numoutlets" : 5,
									"outlettype" : [ "signal", "signal", "", "float", "list" ],
									"parameter_enable" : 1,
									"patching_rect" : [ 15.25, 516.0, 54.0, 102.0 ],
									"saved_attribute_attributes" : 									{
										"valueof" : 										{
											"parameter_longname" : "live.gain~[5]",
											"parameter_shortname" : "live.gain~",
											"parameter_type" : 0,
											"parameter_mmin" : -70.0,
											"parameter_mmax" : 6.0,
											"parameter_initial" : [ 0.0 ],
											"parameter_unitstyle" : 4
										}

									}
,
									"varname" : "live.gain~"
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-93",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 68.5, 639.5, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "1",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 58.75, 238.5, 24.75, 238.5 ],
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-11", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 20 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 19 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 19 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 18 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 18 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 17 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 17 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 16 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 16 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 15 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 15 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 14 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 14 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 13 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 13 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 12 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 12 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 11 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 11 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 10 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 10 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 9 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 9 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 8 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 8 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 7 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 7 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 6 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 6 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 5 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 5 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 4 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 4 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 3 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 3 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 2 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-3", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-33", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-38", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-33", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-38", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-38", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 51.75, 404.0, 24.75, 404.0 ],
									"source" : [ "obj-53", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-53", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-54", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 38.25, 440.75, 24.75, 440.75 ],
									"source" : [ "obj-65", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-9", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-8", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 58.75, 340.0, 24.75, 340.0 ],
									"source" : [ "obj-9", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 10.0, 104.0, 97.0, 20.0 ],
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 13.0,
						"description" : "",
						"digest" : "",
						"fontface" : 0,
						"fontname" : "Arial",
						"fontsize" : 13.0,
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p audio_inputs",
					"varname" : "basic_tab[1]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-5",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 1,
							"revision" : 9,
							"architecture" : "x64"
						}
,
						"rect" : [ 216.0, 118.0, 1337.0, 736.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 13.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 5.0, 5.0 ],
						"gridsnaponopen" : 0,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"bgcolor" : [ 0.8, 0.8, 0.8, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-21",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 158.0, 597.0, 79.0, 18.0 ],
									"text" : "write foo.dsp"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.8, 0.8, 0.8, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-24",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 94.0, 597.0, 36.0, 18.0 ],
									"text" : "write"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-15",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 246.875, 564.0, 264.25, 25.0 ],
									"text" : "external DSP files can be read or written "
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.8, 0.8, 0.8, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-4",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 158.0, 544.0, 77.0, 18.0 ],
									"text" : "read foo.dsp"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.8, 0.8, 0.8, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-55",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 94.0, 543.0, 38.0, 18.0 ],
									"text" : "read"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-3",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 86.0, 733.0, 260.0, 25.0 ],
									"text" : "switch on this dac and test messages..."
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 44.382671,
									"frgb" : 0.0,
									"id" : "obj-16",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 7.0, 5.0, 205.0, 56.0 ],
									"text" : "faustgen~"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"id" : "obj-14",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 7.0, 61.0, 250.0, 20.0 ],
									"text" : "Faust as a Max/MSP external : version 1.12"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-50",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 152.75, 624.0, 96.0, 25.0 ],
									"text" : "view SVG"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-49",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 542.0, 506.25, 162.0, 19.0 ],
									"text" : "set 16 $1 17 $2 18 $3"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-48",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 420.0, 328.5, 62.0, 19.0 ],
									"text" : "set 11 $1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-47",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 344.5, 328.5, 58.0, 19.0 ],
									"text" : "set 1 $1"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-40",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 94.0, 501.0, 108.0, 25.0 ],
									"text" : "mute the DSP"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"bubbleside" : 2,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-39",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 421.0, 352.5, 289.0, 40.0 ],
									"text" : "declare only the first ID for an adjacent group"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-37",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 461.5, 276.5, 327.75, 25.0 ],
									"text" : "you can separately address only one parameter"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"bubbleside" : 2,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-36",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 7.0, 96.0, 711.0, 69.0 ],
									"text" : "This example shows how you can declare a list of parameters messages inside the Faust code for Max. Originally this concept doesn't exist inside Faust, and so was created for the faustgen~ object, to simplify the use of big parameter lists with Max."
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-35",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 152.75, 230.5, 735.0, 40.0 ],
									"text" : "the 2 spaces between \"freq\" and \"0\" are needed to declare \"%3i\" like parameter in the DSP source file, and let you encode a maximum of 999 parameters. If you need more you can declare %4i and 3 spaces between \"freq\" and \"0\"."
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-33",
									"local" : 1,
									"maxclass" : "ezdac~",
									"numinlets" : 2,
									"numoutlets" : 0,
									"ongradcolor1" : [ 0.992157, 0.714953, 0.066136, 1.0 ],
									"patching_rect" : [ 11.0, 725.0, 45.0, 45.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 24.331179,
									"frgb" : 0.0,
									"id" : "obj-25",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 136.0, 288.5, 97.0, 34.0 ],
									"text" : "DECAY"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 24.331179,
									"frgb" : 0.0,
									"id" : "obj-12",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 146.0, 391.25, 77.0, 34.0 ],
									"text" : "GAIN"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.721569, 0.8, 1.0, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-6",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 523.0, 455.25, 44.0, 20.0 ],
									"text" : "+ 300.",
									"textcolor" : [ 0.166497, 0.168367, 0.164626, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-54",
									"maxclass" : "toggle",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 38.0, 478.5, 20.0, 20.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 1.0, 0.435746, 0.304679, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-53",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 38.0, 504.5, 54.0, 18.0 ],
									"text" : "mute $1"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 24.331179,
									"frgb" : 0.0,
									"id" : "obj-34",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 146.0, 172.0, 77.0, 34.0 ],
									"text" : "FREQ"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.721569, 0.8, 1.0, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-22",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "float" ],
									"patching_rect" : [ 479.0, 424.25, 44.0, 20.0 ],
									"text" : "+ 150.",
									"textcolor" : [ 0.166497, 0.168367, 0.164626, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.721569, 0.8, 1.0, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-20",
									"maxclass" : "flonum",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "float", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 435.0, 391.25, 50.0, 20.0 ],
									"textcolor" : [ 0.166497, 0.168367, 0.164626, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.721569, 0.8, 1.0, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-19",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 435.0, 506.25, 99.0, 20.0 ],
									"text" : "prepend freq015",
									"textcolor" : [ 0.166497, 0.168367, 0.164626, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.721569, 0.8, 1.0, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-18",
									"maxclass" : "newobj",
									"numinlets" : 3,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 435.0, 481.25, 107.0, 20.0 ],
									"text" : "pack 0. 0. 0.",
									"textcolor" : [ 0.166497, 0.168367, 0.164626, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.246206, 1.0, 0.266401, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-1",
									"maxclass" : "flonum",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "float", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 406.5, 279.0, 50.0, 20.0 ],
									"textcolor" : [ 0.166497, 0.168367, 0.164626, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.246206, 1.0, 0.266401, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-2",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 406.5, 304.5, 68.0, 18.0 ],
									"text" : "freq010 $1",
									"textcolor" : [ 0.166497, 0.168367, 0.164626, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.246206, 1.0, 0.266401, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-13",
									"maxclass" : "flonum",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "float", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 333.0, 279.0, 50.0, 20.0 ],
									"textcolor" : [ 0.166497, 0.168367, 0.164626, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.246206, 1.0, 0.266401, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-7",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 333.0, 304.5, 68.0, 18.0 ],
									"text" : "freq000 $1",
									"textcolor" : [ 0.166497, 0.168367, 0.164626, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 1.0, 0.717647, 0.984314, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-11",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 50.0, 240.5, 100.0, 20.0 ],
									"text" : "prepend \"freq  0\""
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 1.0, 0.717647, 0.984314, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-9",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 50.0, 340.5, 112.0, 20.0 ],
									"text" : "prepend \"decay  0\""
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 1.0, 0.717647, 0.984314, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-5",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 50.0, 444.5, 102.0, 20.0 ],
									"text" : "prepend \"gain  0\""
								}

							}
, 							{
								"box" : 								{
									"color" : [ 0.8, 0.8, 0.8, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-65",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 24.5, 541.0, 40.0, 20.0 ],
									"text" : "pink~"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
									"candicane2" : [ 0.145098, 0.203922, 0.356863, 1.0 ],
									"candicane3" : [ 0.290196, 0.411765, 0.713726, 1.0 ],
									"candicane4" : [ 0.439216, 0.619608, 0.070588, 1.0 ],
									"candicane5" : [ 0.584314, 0.827451, 0.431373, 1.0 ],
									"candicane6" : [ 0.733333, 0.035294, 0.788235, 1.0 ],
									"candicane7" : [ 0.878431, 0.243137, 0.145098, 1.0 ],
									"candicane8" : [ 0.027451, 0.447059, 0.501961, 1.0 ],
									"candycane" : 4,
									"contdata" : 1,
									"id" : "obj-10",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 50.0, 377.0, 269.0, 62.5 ],
									"peakcolor" : [ 0.498039, 0.498039, 0.498039, 1.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 606.0, 177.0, 196.0, 118.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"setstyle" : 1,
									"size" : 20,
									"slidercolor" : [ 0.890196, 0.647059, 0.992157, 1.0 ],
									"varname" : "Reson-Decay[1]"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
									"candicane2" : [ 0.145098, 0.203922, 0.356863, 1.0 ],
									"candicane3" : [ 0.290196, 0.411765, 0.713726, 1.0 ],
									"candicane4" : [ 0.439216, 0.619608, 0.070588, 1.0 ],
									"candicane5" : [ 0.584314, 0.827451, 0.431373, 1.0 ],
									"candicane6" : [ 0.733333, 0.035294, 0.788235, 1.0 ],
									"candicane7" : [ 0.878431, 0.243137, 0.145098, 1.0 ],
									"candicane8" : [ 0.027451, 0.447059, 0.501961, 1.0 ],
									"candycane" : 4,
									"contdata" : 1,
									"id" : "obj-8",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 50.0, 275.0, 269.0, 61.0 ],
									"peakcolor" : [ 0.498039, 0.498039, 0.498039, 1.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 416.0, 56.0, 196.0, 118.0 ],
									"setminmax" : [ 0.0, 1.0 ],
									"setstyle" : 1,
									"size" : 20,
									"slidercolor" : [ 0.890196, 0.647059, 0.992157, 1.0 ],
									"varname" : "Reson-Decay"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 1.0, 1.0, 1.0, 0.0 ],
									"candicane2" : [ 0.145098, 0.203922, 0.356863, 1.0 ],
									"candicane3" : [ 0.290196, 0.411765, 0.713726, 1.0 ],
									"candicane4" : [ 0.439216, 0.619608, 0.070588, 1.0 ],
									"candicane5" : [ 0.584314, 0.827451, 0.431373, 1.0 ],
									"candicane6" : [ 0.733333, 0.035294, 0.788235, 1.0 ],
									"candicane7" : [ 0.878431, 0.243137, 0.145098, 1.0 ],
									"candicane8" : [ 0.027451, 0.447059, 0.501961, 1.0 ],
									"candycane" : 4,
									"contdata" : 1,
									"id" : "obj-17",
									"maxclass" : "multislider",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "", "" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 50.0, 165.0, 269.0, 60.0 ],
									"peakcolor" : [ 0.498039, 0.498039, 0.498039, 1.0 ],
									"presentation" : 1,
									"presentation_rect" : [ 175.0, 57.0, 196.0, 118.0 ],
									"setminmax" : [ 20.0, 3000.0 ],
									"setstyle" : 1,
									"size" : 20,
									"slidercolor" : [ 0.890196, 0.647059, 0.992157, 1.0 ],
									"varname" : "Reson-Freq"
								}

							}
, 							{
								"box" : 								{
									"bitcode" : "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",
									"bitcode_size" : 29036,
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"id" : "obj-32",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 11.0, 626.5, 141.0, 20.0 ],
									"serial_number" : "C02JV2K0DKQ464 bits",
									"sourcecode" : "import(\"stdfaust.lib\"); \r\n\n// Example programmed by Christophe Lebreton - GRAME\r\n\nf(i) = hslider(\"freq%3i\", 160.,-0.,20000.,0.001);\nr(i) = hslider(\"decay%3i\", 0.,0.,1.,0.001):((pow(4.78)*6)+0.0001):ba.tau2pole;\ng(i) = hslider(\"gain%3i\", 0.,0.,1.,0.0001);\n\nresonator(n) = _<:par(i,n,*(g(i)):fi.nlf2(f(i),r(i)):_,!:*(ba.db2linear((100*(log(1/r(i))))))):>*(0.003162);\n\nprocess  = resonator(20) ;",
									"sourcecode_size" : 520,
									"text" : "faustgen~",
									"varname" : "faustgen-12d371c0",
									"version" : "1.12"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"hidden" : 1,
									"id" : "obj-23",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 214.0, 7.0, 59.5, 20.0 ],
									"restore" : 									{
										"Reson-Decay" : [ 0.644068, 0.38983, 0.38983, 0.355932, 0.40678, 0.457627, 0.497175, 0.536723, 0.576271, 0.618644, 0.661017, 0.677966, 0.694915, 0.694915, 0.694915, 0.694915, 0.644068, 0.525424, 0.491525, 0.288136 ],
										"Reson-Decay[1]" : [ 0.516667, 0.483333, 0.483333, 0.433333, 0.433333, 0.433333, 0.433333, 0.433333, 0.433333, 0.433333, 0.583333, 0.483333, 0.3, 0.3, 0.3, 0.283333, 0.25, 0.666667, 0.6, 0.116667 ],
										"Reson-Freq" : [ 1355.862061, 1355.862061, 1201.724121, 379.655182, 1047.586182, 893.448303, 944.827576, 893.448303, 739.310364, 739.310364, 739.310364, 739.310364, 739.310364, 739.310364, 687.93103, 533.793091, 379.655182, 225.517242, 122.758621, 1407.241333 ],
										"live.gain~" : [ -19.874891 ]
									}
,
									"text" : "autopattr",
									"varname" : "u820000124"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-38",
									"maxclass" : "live.gain~",
									"numinlets" : 2,
									"numoutlets" : 5,
									"outlettype" : [ "signal", "signal", "", "float", "list" ],
									"parameter_enable" : 1,
									"patching_rect" : [ 11.0, 659.5, 54.0, 50.0 ],
									"saved_attribute_attributes" : 									{
										"valueof" : 										{
											"parameter_longname" : "live.gain~[4]",
											"parameter_shortname" : "live.gain~",
											"parameter_type" : 0,
											"parameter_mmin" : -70.0,
											"parameter_mmax" : 6.0,
											"parameter_initial" : [ 0.0 ],
											"parameter_unitstyle" : 4
										}

									}
,
									"varname" : "live.gain~"
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-93",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 63.5, 735.0, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "1",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-2", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-48", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-10", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 59.5, 266.5, 20.5, 266.5 ],
									"source" : [ "obj-11", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-47", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-13", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-7", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-13", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-11", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-17", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-19", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-18", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-49", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-18", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 444.5, 533.75, 20.5, 533.75 ],
									"source" : [ "obj-19", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 416.0, 533.0, 20.5, 533.0 ],
									"source" : [ "obj-2", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-18", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-20", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-22", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 444.5, 417.25, 488.5, 417.25 ],
									"source" : [ "obj-20", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-21", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-18", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-22", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-6", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 488.5, 449.25, 532.5, 449.25 ],
									"source" : [ "obj-22", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-24", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-38", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-32", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-33", 1 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-38", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-33", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-38", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-4", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-17", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-47", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-17", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-48", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-17", 0 ],
									"disabled" : 0,
									"hidden" : 1,
									"source" : [ "obj-49", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 59.5, 473.5, 20.5, 473.5 ],
									"source" : [ "obj-5", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 47.5, 533.0, 20.5, 533.0 ],
									"source" : [ "obj-53", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-53", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-54", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-55", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-18", 2 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-6", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 34.0, 569.75, 20.5, 569.75 ],
									"source" : [ "obj-65", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 342.5, 533.0, 20.5, 533.0 ],
									"source" : [ "obj-7", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-9", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-8", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-32", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 59.5, 368.0, 20.5, 368.0 ],
									"source" : [ "obj-9", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 10.0, 77.0, 119.0, 20.0 ],
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 13.0,
						"description" : "",
						"digest" : "",
						"fontface" : 0,
						"fontname" : "Arial",
						"fontsize" : 13.0,
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p messages_inputs",
					"varname" : "basic_tab[4]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-2",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 1,
							"revision" : 9,
							"architecture" : "x64"
						}
,
						"rect" : [ 0.0, 26.0, 1337.0, 736.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 13.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 5.0, 5.0 ],
						"gridsnaponopen" : 0,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 44.382671,
									"frgb" : 0.0,
									"id" : "obj-16",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 7.0, 5.0, 205.0, 56.0 ],
									"text" : "faustgen~"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"id" : "obj-14",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 7.0, 61.0, 250.0, 20.0 ],
									"text" : "Faust as a Max/MSP external : version 1.12"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-2",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 44.0, 393.5, 716.0, 25.0 ],
									"text" : "it's free..... what else.. ;)"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"bubbleside" : 2,
									"fontname" : "Arial",
									"fontsize" : 16.0,
									"frgb" : 0.0,
									"id" : "obj-10",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 7.0, 91.219208, 817.0, 43.0 ],
									"text" : "After evaluating your faustgen~ code with your Max6, you may possibly want to use it with other architectures."
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-9",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 44.0, 358.5, 866.0, 25.0 ],
									"text" : "since the language of mathematic has a slower evolution than computer architectures, it'll be easier to reuse this code in the future !"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-7",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 44.0, 322.0, 716.0, 25.0 ],
									"text" : "it's a good way to get directly with Latex a big poster of mathematic equation of your DSP code for Halloween..."
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-5",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 44.0, 276.5, 993.0, 40.0 ],
									"text" : "it's a good way to get your code for 32 bits Max5, or generate it for VST, Max Windows version, PureData, iPad... or any other target architecture available on the Faust online compiler..."
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-3",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 44.0, 242.5, 834.0, 25.0 ],
									"text" : "it's a good way to get your Max6 fausgen~ object as as statically compiled Max6 object (without possibility to break it anymore !)"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"bubbleside" : 2,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-6",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 90.0, 135.219208, 600.0, 55.0 ],
									"text" : "A web compiler is here for you to get your specific object without any SDK installed on you computer, you have to copy/paste your faustgen~ code to this online compiler"
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.992157, 0.714953, 0.066136, 1.0 ],
									"fontname" : "Arial",
									"fontsize" : 13.051434,
									"id" : "obj-1",
									"linecount" : 2,
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 174.5, 190.219208, 420.0, 34.0 ],
									"text" : ";\rmax launchbrowser http://faust.grame.fr/compiler/"
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-93",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 23.0, 243.5, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "1",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-11",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 23.0, 396.5, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "5",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-12",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 23.0, 359.5, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "4",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-8",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 23.0, 323.0, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "3",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-4",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 23.0, 286.0, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "2",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
 ],
						"lines" : [  ]
					}
,
					"patching_rect" : [ 10.0, 159.0, 97.0, 20.0 ],
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 13.0,
						"description" : "",
						"digest" : "",
						"fontface" : 0,
						"fontname" : "Arial",
						"fontsize" : 13.0,
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p web_compiler",
					"varname" : "basic_tab[2]"
				}

			}
, 			{
				"box" : 				{
					"fontname" : "Arial",
					"fontsize" : 12.0,
					"id" : "obj-3",
					"maxclass" : "newobj",
					"numinlets" : 0,
					"numoutlets" : 0,
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 6,
							"minor" : 1,
							"revision" : 9,
							"architecture" : "x64"
						}
,
						"rect" : [ 0.0, 26.0, 1337.0, 736.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 13.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 0,
						"gridsize" : [ 5.0, 5.0 ],
						"gridsnaponopen" : 0,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"boxanimatetime" : 200,
						"imprint" : 0,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"showontab" : 1,
						"boxes" : [ 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 10.0,
									"frgb" : 0.0,
									"id" : "obj-51",
									"linecount" : 4,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 225.5, 5.0, 299.0, 51.0 ],
									"text" : "Faust site : http://faust.grame.fr\nFaust development: GRAME\nfaustgen~ programmation: Martin Di Rollo, Stéphane Letz\nHelp patch : Christophe Lebreton"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-48",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 510.0, 236.5, 506.0, 54.0 ],
									"text" : "close the edit window launches a new compile if the code has been changed. When you save a patch, compiled faustgen code is saved in a binary format and doesn't need to be recompiled at next launch"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-47",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 593.0, 87.0, 499.0, 40.0 ],
									"text" : "copy/paste a faustgen~ without a name argument let you copy this object with his current code as a new instance to be modified without dependency..."
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-27",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 325.0, 728.0, 474.0, 54.0 ],
									"text" : "the most important part to start, use and call code already existing for Faust. \nLike famous effect.lib and filter.lib of Julius O.Smith and music.lib of Yann Orlarey the creator of this DSP language... etc..."
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-28",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 141.0, 736.0, 183.0, 25.0 ],
									"text" : "View libraries",
									"underline" : 1
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-44",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 325.0, 682.5, 502.0, 40.0 ],
									"text" : "open the actual .pdf documentation of the Faust language. \n(possibly takes some time the first time you open it for this object...) "
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-45",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 141.0, 690.0, 183.0, 25.0 ],
									"text" : "View PDF documentation",
									"underline" : 1
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-40",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 303.0, 651.5, 526.0, 25.0 ],
									"text" : "very usefull to better understand what you program in the Faust language"
								}

							}
, 							{
								"box" : 								{
									"bitcode" : "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",
									"bitcode_size" : 8192,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-41",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 7.0, 653.5, 100.0, 21.0 ],
									"serial_number" : "C02JV2K0DKQ464 bits",
									"sourcecode" : "import(\"stdfaust.lib\"); \n\nencore_du_cable(n) = _<:par(i,n,*):>*(0);\n\nprocess = encore_du_cable(256);",
									"sourcecode_size" : 241,
									"text" : "faustgen~",
									"varname" : "faustgen-12f78790",
									"version" : "1.12"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-42",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 141.0, 651.5, 162.0, 25.0 ],
									"text" : "View SVG diagram",
									"underline" : 1
								}

							}
, 							{
								"box" : 								{
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-39",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 9.0, 619.5, 877.0, 21.0 ],
									"text" : "IMPORTANT: all code you create with the Faust language can later be compiled for many different architectures --> see \"web_compiler\" tab"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-38",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 116.5, 572.5, 690.5, 36.0 ],
									"text" : "Nota: in next release some others options will be available and a automatic optimisation mode will be let you directly get the best option for your computer and application..."
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-35",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 225.5, 549.0, 689.0, 25.0 ],
									"text" : "is vectorial mode with a vector size at 64 (by default is 32. Will be a power of 2 minus or equal at \"svs\" of maxmsp)"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-36",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 59.0, 549.0, 163.0, 19.0 ],
									"text" : "compileoptions -vec -vs 64"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-33",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 198.0, 519.0, 263.0, 25.0 ],
									"text" : "is vectorial mode with another option"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-34",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 40.0, 522.0, 153.0, 19.0 ],
									"text" : "compileoptions -vec -lv1"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-32",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 157.0, 492.0, 304.0, 25.0 ],
									"text" : "is vectorial mode ( with \"-lv0\" by default )"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-31",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 141.0, 465.0, 369.0, 25.0 ],
									"text" : "this message without argument compiles in \"scalar\" mode "
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-30",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 7.0, 469.0, 125.0, 19.0 ],
									"text" : "compileoptions"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-29",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 25.0, 495.0, 125.0, 19.0 ],
									"text" : "compileoptions -vec"
								}

							}
, 							{
								"box" : 								{
									"bitcode" : "3sAXCwAAAAAUAAAAWBgAAAcAAAFCQ8DeIQwAABMGAAALgiAAAgAAABIAAAAHgSORQcgESQYQMjmSAYQMJQUIGR4Ei2KAHEUCQpILQuQQMhQ4CBhJCjJEJEgKkCEjxFKADBkhciQHyMgRYqigqEDG8AEAAABRGAAAFAAAABuIIACWDYTw/////wMgbTCG/////x8ACaA2EAQAJBuMIgAWgNpgGAKwANUG4wiABag2GMj/////D4AEVBuQZAASYAGqDYhCAAmwABUAAAAASRgAAAgAAAAThECYIATDBIEQJgiFMUE4kAlCMUwIhgnBMYEoEkUAAIkgAABNAAAAMiLICSBkhQSTI6SEBJMj44ShkBQSTI6MC4TkTBCcwxwBkhIACiQLgAZZAaBCUgDokBoASmQLgBbZAaBGjgDokRsAiiQGgCYZAaBKEgDokhMAyiQCgDYJAaBOFgDokykACqUBgEbpAKBSNgDolA8ASqUFgFaZAaBWXgDoNQJAgCLEZDSbIwCDe6QpooTJH6SHwQbpQUGNbEWI3Qg3RwAKRZDpaFeCG/XKEJPJ6DcEQMFCxGQyIQ0LEpPJhMFgMEjFYsRkMmEwSMdSxGRCmYyS10hTRAmT74rgQhGokQGBQBqRaDQakUglLcsQuzGpWYTajZ5lqN1qFC1CrEbTMsRuNaoWIiaTyeh6jzRFlDD5JjEB4EIRSJBhKVuEmJa2JCxF7FbrdslLMgISjWpzBAFhpwAAAAATMnzAAzv4BTuggzYIB3iAB3YohzYgh3CQh3tIB3eIAzlwAztwAzjYgBbl0AbwoAd2QAd6YAd0oAd2QAdtMAtxIAd40AbpEAd6gAd6gAdtkA54oAd4oAd40AbpEAd2oAdxYAd6EAd20AbpMAdyoAdzIAd6MAdy0AbpYAd0oAd2QAd6YAd00AbmEAd2oAdxYAd6EAd20AbmMAdyoAdzIAd6MAdy0AbmYAd0oAd2QAd6YAd00AbmEAdygAd6EAdygAd6EAdygAdtYA92QAd6YAd0oAd2QAdtYA9xIAd4oAdxIAd4oAdxIAd40AbhAAd6AAd6YAd00AbzAAd6YAd0oAd2QAdtYA54AAd6EAdygAd6EAdygAdt4A54oAdxYAd6MAdyoAd2QAc6D8RIICNERAAKbWEgsRcGGn1hIJIcBirRYSAzHQY61WEglB0GSt1hoPAWBlLjYaBVHgZK32Eg1h4GavNhIFckBnpHYqAUHgZq9WEgGCUGCnFhoPEXBmr3YaCXJAYawWGgMRwGiltioJYfBoJTYqC3JAaSXWKgth8GWudhILIcBpphYiBaJgZa6WGgMBcGGsVhoNYfBoJVYqDXJAY612Gg9h8GYu9hoLUeBiLNYaBQFwaqZ2KgOSYGCndhILsmBrptYiAcJwYiz2Gg+yYGwnNiIHglBgp5YSC0HQYax2Eg+SUGakFioPckBqppYqA2JAZi8WEgmCWGIQsdAAEQCAAAAMCQJQ8AABAEAAAAYMiSBwAABAAAAAAwZOEDIAAGAAAAABiy5AEAAIIAAAAADFn8AACAAQAAAACGLK4AAAAhAAAAAEMWWAAAoAAAAACAIQssAABgAAAAAMCQBRYAADAAAAAAYMgiCwAAGAAAAAAwZJEFAAAMAAAAABiy0AIAAAcAAAAADFlsAQCAAAAAAACGLLwAAAACAAAAAEOWXwAAIAEAAACAIYstAAAQAAAAAEAWCCwBAAAyHpggGRFMkIwJJkfGBEMKaFQ2m8tjuoudFr/CdTr6LdeomaSCmOlx2T0vg1DNJDWlkTnNppflLnZa/ArX6ei3XKN2GN+ew13stPgVrtPRb7lG7fo8PXax0+IXOz0uu+dljdr1eXrsYqfFL3tZPk+/3RrJy+T6uOxip8WvcJ2OfstpoGugrLPT9Tno6QJN22k6GoRSv+egMB00HsvbYdecHnab33Kyq0yup6igVNlsLo/pLnZa/Bq/4Xl5+oymK2VOs+lluYudFr/Gb3henj6j6UoZw/U5HWRMs+llOYiZFsvD8rxS5jSbXpa72GnxS142l+Vl97isVDuMb8/hLnZa/Bq/4Xl5+oymKyUvk+vjsoudFr/Gb3henj6j6XTQSVlnp+tz0NMFmrbTdDQomUzqxDxCmaB7mo4GlfHjMpyefrt1atfn6bGLnRa/xm94Xp4+o+k6vefjNJsdpr/lLnZa/HKH22VKaFY2m8tjuoudFr/K+HGaXpZ/w3U6+i2nhbIBVJ7Oh93rMGiKLq/DchAKPkeX12H5dzyWt8OuOT3sNr/lZFeZXE9RQ7my2Vwe013stPhVxo/T9LL8O37D8/L0GU1XrhnGN6dQ0PjdhofpaXGanabnQcy0WB6W5+mhYjB8w/Py9BlNB6HGKZAMFpuBoPJ0Puxeh0FTdHkdlqsYZMNuN+gpZ4fl5TwI9Zazw/JyHhSmg87ycLvsMstTFFGtbDaXx3QXOy1+lfHjNL0s/7LT47J7XlatbDaXx3QXOy1+lfHjNL0s/9rL8nn67VbNGK7P6aBgnZx+g4pmc3lMBzHTYnlYnqeJXmWzuTymu9hp8auMH6fpZfnXHW6XqaIQMixvv93pMaiIH6fpZblC7TAd7WKnxS92elx2z8sKtcN0tIudFr/sZfk8/XYr1K7P02MXOy1+het09FtOlx1qn96h9usdaL+mjEpls7k8prvYafGLnR6X3fOySmWzuTymu9hp8ctels/Tb7dK5jSbXpa72Gnxi50el93zskrmNJtelrvYafHLXpbP02+3Su0wHe1ip8Wv8Ruel6fPaLpK7TC+PYe72Gnxi50el93zskrtML49h7vYafHLXpbP02+3SvIyuT4uu9hp8YudHpfd87JK8jK5Pi672Gnxy16Wz9NvN230mFKXLZprRh19ymZzeUx3sdPilzvcLutjTrPpZbmLnRa/3OF2WZ92mI52sdPiV7hOR7/l+rTD+PYc7mKnxS93uF3WR14m18dlFzstfrnD7TJ9lqj9+16i9u1+iRJMyyVqv66XoC+appCiAZpOh891r9d4LG+HXXN62G1+y8muMrn+8qvf85c5zaaX5fMXjbYAV830tgAjgCGopE07TEe72Gnxyx1ul7Vp1ufpMYiZFsvD8jydlGmG6WgQMy2Wh+V5SqnTrs/TYxc7LX65w+2yOtIyuT4ug5hpsTwsz9NKq/d8nGazw/S33MVOi1/hOh39llNLsfd8nGazw/S33MVOi1/jNzwvT5/RdMWM4fqcDnrOx2k2O0x/y0HMtFgelufppdZ7Pk6z2WH6W+5ip8Uvdnpcds/Lar3n4zSbHaa/5S52Wvyyl+Xz9NsNAAB5GAAAFwAAADMIgBzE4RxmFAE9iEM4hMOMQoAHeXgHc5hxDOYAD+0QDvSADjMMQh7CwR3OoRxmMAU9iEM4hIMbzAM9yEM9jAM9zHiMdHAHewgHeUiHcHAHenADdniHcCAHAAAAcSAAAGYBAABmtAzEQkwEgw3SY02SQUwnxaDU9FCTxGCD9BgRUUQEUQOTss5O1+egpws0bafpaFAymbQJovbv24YI+qJpc4oMYhKbh5pWYCIYbJCeosHe83GazQ7T33IXOy1+jd/wvDx9RtPNowBXzfSspwAjgCEKyJGWyfVxGcRMi+Vhed4ahtqnjWWo/boC1kBZZ6frc9DTBZq203Q0CKV+z0FhOmg8lrfDrjk97Da/5WRXmVxPGVIDLIsjABPBYIP0VI31no/TbHaY/pa72Gnxi50el93zcj0cU+qyRXPNKqZp1ufpMYiZFsvD8rwlIQ1hMdggPfUhtcN0tIudFr/Gb3henj6j6cWglc3m8pjuYqfFrzJ+nKaX5V97WT5Pv91lM73n4zSbHaa/5S52Wvxyh9vlKmADqDydD7vXYdAUXV6H5SAUfI4ur8Py73gsb4ddc3rYbX7Lya4yuZ4ypsggppNixOahJonBBukpEKgdpqNd7LT4xU6Py+552agSpEEmBhukp0yodhjfnsNd7LT4NX7D8/L0GU2vBQgZlrff7vQYVMSP0/SyvHgoeZlcH5dd7LT4NX7D8/L0GU2vEaYZpqNBzLRYHpbn6+eRl8n1cdnFTotf7nC7bEpXQCHL4EpEJDYTERWAQDDYID0m1TDEBAzABDDYID3lI8nL5Pq47GKnxS92elx2z8t1IAbDNzwvT5/RdBBqnALJYLEZCCpP58PudRg0RZfXYXl1PO0wHe1ip8WvcJ2OfsurgjKn2fSy3MVOi1/jNzwvT5/R9LrBjOH6nA56zsdpNjtMf8tBzLRYHpbnC8d6z8dpNjtMf8td7LT4ZS/L5+m324qYgZCmyMEYbJCeeona9Xl67GKnxS92elx2z8sVMjGPUCbonqajQWX8uAynp9/uOpHaYXx7Dnex0+IXOz0uu+flspDMaTa9LHex0+IXOz0uu+flKonaYXx7Dnex0+JXuE5Hv+WWQ9R+XZeDVDaby2O6i50Wv9jpcdk9LxcJ1A7T0S52Wvyyl+Xz9NtdBFnZbC6P6S52Wvwq48dpeln+Ddfp6Le8EqJmkgpipsdl97wMQjWT1JQ9SQYxodT0UNMKTASDDdJTO2KQDbvdoKecHZaX8yDUW84Oy8t5UJgOOsvD7bLLLE8VRWROs+lluYudFr/CdTr6LTehgfbrWpHaYXx7Dnex0+KXvSyfp9/uCpLkZXJ9XHax0+KXvSyfp9/ugnHa9Xl67GKnxS93uF0umahdn6fHLnZa/LKX5fP0210aaICm0+Fz3es1HsvbYdecHnab33Kyq0yuv/zq9/xlTrPpZfn8VRiUMVyf00HGNJteloOYabE8LM+XSNMO09Eudlr8cofb5dqQzGk2vSx3sdPil70sn6ff7oJ4ymZzeUx3sdPilzvcLtdM9Z6P02x2mP6Wu9hp8Stcp6Pf8lLhmmF8cwoFjd9teJieFqfZaXoexEyL5WF5viSkstlcHtNd7LT4ZS/L5+m3u1qgdn2eHrvYafErXKej3/LKoMxpNr0sd7HT4pe8bC7Ly+5x2TiI2rf7SnnaYXx7Dnex0+KXO9wulwFXNpvLY7qLnRa/yvhxml6Wf8dveF6ePqPp5TK16/P02MVOi1/jNzwvT5/RdEMhSjAtbYoRHOahJoLBBukpgKhsNpfHdBc7LX6F63T0W14KV9lsLo/pLnZa/Crjx2l6Wf51h9tli4qQRpqARiDEBpkYbJCeitCM4fqcDgrWyek3qGg2l8d0EDMtlofl+ULQymZzeUx3sdPiVxk/TtPL8i87PS6752U7MhhgWRzBoBxhASRJbJCJwQbpqYvHnGbTy3IXOy1+ucPtsi1JBjGxAPMsxApMBIMN0lMCVNlsLo/pLnZa/Bq/4Xl5+oyml04kL5Pr47KLnRa/wnU6+i0HAAAAYSAAAAkAAAATBAGGAwEAAAUAAACWGTAM0nMAC9FMEfYHiyMoAAAAAAAAAABhIAAACQAAABMEwQWyHTEggOAWAgwHAgADAAAAB1AQzRRhlhkwDNIDAAAAAGEgAAAJAAAAEwQBhgMBAAAFAAAAlhkwDNJzAAvRTBH2B4sjKAAAAAAAAAAAYSAAAAwAAAATBEEsEAAAAAEAAACkKyAAIwYEEMxCcMFtMwgHAgAAAAIAAAAHUBDNFGEAAAAAAABhIAAAGQAAABMEQSwQAAAABgAAAKQbAaDaCEAZFALJhjLAYBTqgCfqgCcAAGeAlwIw3oAcBQVgxKAAgmAoxhuUxKAAjBgQQBAUGA4EBgAAAKYZkCDNREQFIBAHQCANMllmwDBIDwAAAAAAAABhIAAACgAAABMEwQXjpQBkEA4EAAUAAACWGTAM0nMAC9FMEfYHiyMoAAAAAAAAAABhIAAADAAAABMEQSwQAAAAAQAAAFQrAgAZhAMBBQAAAJYZMAzScwAL0UwR9geLIygAAAAAAAAAAGEgAAAMAAAAEwRBLBAAAAABAAAAVCsCABmEAwEFAAAAlhkwDNJzAAvRTBH2B4sjKAAAAAAAAAAAYSAAABUAAAATBEEsEAAAAAIAAABUK4ISqAEAAMMNxEAG0w2DEGQQDgQAAAAKAAAA5hlgSBYyCYdlBgyD9JhmwCEcQNMQywEsRDNF2B8sjqDYZ0DgAwAAAAAAAABhIAAAFQAAABMEQSwQAAAAAgAAAFQrghKoAQAAww3EQAbTDYMQZBAOBAAAAAoAAADmGWBIFjIJh2UGDIP0mGbAIRxA0xDLASxEM0XYHyyOoNhnQOADAAAAAAAAAGEgAAAKAAAAEwQBhgMBAAAGAAAAlhnASADzLEhjfBEBHcBCNFOE/cHiCAoAAAAAAGEgAAAOAAAAEwTBCeMdjAgEAMBwIAAAAAgAAACWGTAM0mOaAYwEMM+CNMYXEdABLEQzRdgfLI6gAAAAAAAAAABhIAAADAEAABMEQSwQAAAArAAAAKQbAaBaCYwAkGwoA2vqgCfqgCeGMrinDniiDnhiKAMJgzrgiTrgiaEMMECDOuCJOuCJoQwBqAOeqAOeGMowhDrgiTrgiaEMhagDnqgDnhjKYIo64Ik64ImhDMeoA56oA54YyoCOOuCJOuCJoQwJqQOeqAOeGMoQkjrgiTrgiaEMSqkDnqgDnhjKsJY64Ik64ImhDImpA56oA54YytCcOuCJOuCJoQwPqgOeqAOeGMqQojrgiTrgiaEMTaoDnqgDnhjKAIOpDniiDnhiKEOg6oAn6oAnhjKMqg54og54YihDs+qAJ+qAJ4YyvKsOeKIOeGIow8DqgCfqgCeGMoysDniiDnhiKEMMtDrgiTrgiaEMbasDnqgDnhjKAAOuDniiDnhiKMPr6oAn6oAnhjK0rw54og54YijDAoM64Ik64ImhDDMQgzrgiTrgiaEMNBiDOuCJOuCJoQyLDOqAJ+qAJ4YyhDKoA56oA54YyjDMoA54og54YihDO4M64Ik64ImhDC8N6oAn6oAnhjIcNagDnqgDnhjK0NagDniiDnhiKANjgzrgiTrgiaEMqw3qgCfqgCeGMhA3qAOeqAOeGMoQ3qAOeKIOeGIoQw3goA54og54YijDDOKgDniiDnhiKEOQgzrgiTrgiaEMNpiDOuCJOuCJoQw3oIM64Ik64ImhDDiogzrgiTrgiaEMxA7qgCfqgCeGMtzgDuqAJ+qAJ4Yy4AAP6oAn6oAnhjLAIA/qgCfqgCeGMgQ9qAOeqAOeGMqA9qAOeKIOeGIow+CDOuCJOuCJoQwy6IM64Ik64ImhDM0P6oAn6oAnhjK8P6gDnqgDnhjKUANQqAOeqAOeGMrQQqEOeKIOeGIoAxOFOuCJOuCJoQxkqAOeqAOeGMoggjrgiTrgiaEMMvDqgCfqgCcAAAB3CuClAAwxpAIqnAIFYMTAAIJgGAVjxMAAgmAQhWPEwACCYAgFUBgxMIAgGP7AD0YMDCAIhj7ggxEDAwiCYQ/0YMTAAIJgyINTGDEwgCAY8MAURgwMIAiGO7CDEQMDCIKhDuhgxMAAgmCYA2PEwACCYJCDY8TAAIJgiANTGDEwgCAY4OANRgwMIAgGN2iDEQMDCIKBDdZgxMAAgmBQg2LEwACCYEiDYsTAAIJgQINSGDEwgCAYzsAMRgwMIAiGMjiFEQMDCIKBDIoRAwMIgmEMihEDAwiCQQxIYcTAAIJgCAMwGDEwgCAYPm/EwACCYOiKEQMDCIKBK0YMDCAIhq0URgwMIAgGLRsxMIAgGLBTGDEwgCAYLmPEwACCYLCOEQMDCIKhMoURAwMIgoGaRgwMIAgGKRoxMIAgGKBnxMAAgmBwmhEDAwiCgSGFEQMDCIJhUUYMDCAIhgTBcCAEAAAAB7AQzRRhf7A4gmKZAQEDAAAAAABhIAAATgAAABMERCwQAAAAAwAAAFQbASiBGiBdCQAAAMMNB2EGswzBEIwnGMR4AlKQACgBNABiwCyBMFBRB5fABQMVojAJRjBQIQqPwAQDFaKwCEgwUCEKh+AEJIDBCCEAACrAYEQRAMAQwvAMIRTQEMIRDSEkUi0UDDcEFxjMMgxCgOFAAAAALAAAADdgRMRERY1tBhhI81CTZJwBh0NNDzVJFhuASAJRGcTDG2wAIglEZRCPbpkBwyA9phlQCA7VTDYbsCxS5COV3xDXZK8BhyQQlUE8JhuQSAJRGcRT04YacCxS5CNVbasBxyJFPlLlphpwLFLkI9V+AovgDMQfLI6g2JYacCxS5CNVfwGV4AzEHyyOoNj+ExEHAQxEdAAL0UwR9geLIyjGGmAsUuQjldEGIMSFTILTDAAAAAAAAGEgAAAOAAAAEwTBCeMdjAgEAMBwIAAAAAgAAACWGTAM0mOaAYwEMM+CNMYXEdABLEQzRdgfLI6gAAAAAAAAAAAAAAAAAAAAAA==",
									"bitcode_size" : 8344,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-26",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "signal" ],
									"patching_rect" : [ 7.0, 587.5, 100.0, 21.0 ],
									"serial_number" : "C02JV2K0DKQ464 bits",
									"sourcecode" : "import(\"stdfaust.lib\"); \n \nprocess = _,_;",
									"sourcecode_size" : 176,
									"text" : "faustgen~",
									"varname" : "faustgen-12fad570",
									"version" : "1.12"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-25",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 303.0, 426.5, 583.0, 40.0 ],
									"text" : "faustgen~ compiles by defaut with \"double\" samples (64 bits) in scalar mode and print it in the Max Window"
								}

							}
, 							{
								"box" : 								{
									"bitcode" : "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",
									"bitcode_size" : 8344,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-22",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "signal" ],
									"patching_rect" : [ 7.0, 428.5, 100.0, 21.0 ],
									"serial_number" : "C02JV2K0DKQ464 bits",
									"sourcecode" : "import(\"stdfaust.lib\"); \n \nprocess = _,_;",
									"sourcecode_size" : 176,
									"text" : "faustgen~",
									"varname" : "faustgen-12fd4bf0",
									"version" : "1.12"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-13",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 141.0, 426.5, 162.0, 25.0 ],
									"text" : "View compile options",
									"underline" : 1
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-24",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 141.0, 361.5, 162.0, 25.0 ],
									"text" : "View DSP parameters",
									"underline" : 1
								}

							}
, 							{
								"box" : 								{
									"bgcolor" : [ 0.690412, 1.0, 0.13811, 1.0 ],
									"bubble" : 1,
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-23",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 141.0, 208.0, 130.0, 25.0 ],
									"text" : "Edit DSP code",
									"underline" : 1
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-21",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 271.0, 208.0, 344.0, 25.0 ],
									"text" : "double click on faustgen~ to open a selection menu"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-20",
									"local" : 1,
									"maxclass" : "ezdac~",
									"numinlets" : 2,
									"numoutlets" : 0,
									"ongradcolor1" : [ 0.992157, 0.714953, 0.066136, 1.0 ],
									"patching_rect" : [ 87.0, 298.0, 45.0, 45.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-19",
									"maxclass" : "flonum",
									"numinlets" : 1,
									"numoutlets" : 2,
									"outlettype" : [ "float", "bang" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 7.0, 310.0, 50.0, 21.0 ]
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-18",
									"maxclass" : "message",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 7.0, 339.0, 55.0, 19.0 ],
									"text" : "gain $1"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-17",
									"maxclass" : "live.meter~",
									"numinlets" : 1,
									"numoutlets" : 1,
									"orientation" : 1,
									"outlettype" : [ "list" ],
									"patching_rect" : [ 7.0, 396.5, 100.0, 5.0 ]
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-11",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 303.0, 354.0, 560.0, 54.0 ],
									"text" : "this example let you see how to declare a slider to replace an audio input.\nyou can see it with SVG diagram but also in the Max Window with \"View DSP parameters\"\nand see how the sliders are declared"
								}

							}
, 							{
								"box" : 								{
									"bitcode" : "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",
									"bitcode_size" : 8472,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-10",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 7.0, 364.0, 100.0, 21.0 ],
									"serial_number" : "C02JV2K0DKQ464 bits",
									"sourcecode" : "import(\"stdfaust.lib\"); \n \nprocess = (1)*(gain)\r\n\t\twith {\r\n\t\t\tgain = vslider(\"gain [unit:linear]\", 0,0,1,0.001);\r\n\t\t\t};",
									"sourcecode_size" : 254,
									"text" : "faustgen~",
									"varname" : "faustgen-12fe5f00",
									"version" : "1.12"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-9",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 141.0, 298.0, 630.0, 40.0 ],
									"text" : "the DAC can stay on during a faust code edition. The sound is automatically muted only during a new compilation"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-7",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 141.0, 243.5, 369.0, 40.0 ],
									"text" : "for example change the code by \" process = +,+; \"\nto see inlets and outlets of object \"faustgen~ plus\" changes"
								}

							}
, 							{
								"box" : 								{
									"bitcode" : "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",
									"bitcode_size" : 8280,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-5",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 9.0, 210.5, 100.0, 21.0 ],
									"serial_number" : "C02JV2K0DKQ464 bits",
									"sourcecode" : "import(\"stdfaust.lib\"); \n \nprocess = +;",
									"sourcecode_size" : 175,
									"text" : "faustgen~ plus",
									"varname" : "faustgen-fbb3730",
									"version" : "1.12"
								}

							}
, 							{
								"box" : 								{
									"bitcode" : "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",
									"bitcode_size" : 8280,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-4",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 1,
									"outlettype" : [ "signal" ],
									"patching_rect" : [ 9.0, 156.0, 100.0, 21.0 ],
									"serial_number" : "C02JV2K0DKQ464 bits",
									"sourcecode" : "import(\"stdfaust.lib\"); \n \nprocess = +;",
									"sourcecode_size" : 175,
									"text" : "faustgen~ plus",
									"varname" : "faustgen-fc5dcb0",
									"version" : "1.12"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-2",
									"linecount" : 3,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 141.0, 139.5, 606.0, 54.0 ],
									"text" : "argument is to specify a \"name\" of this instance and share the same faust code with all objects with this name. If you load anoother patch with a same faustgen~ name, you'll keep the current code. Be carefull, if you change the name you loose your previous code (copy it before ;)"
								}

							}
, 							{
								"box" : 								{
									"bubble" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"frgb" : 0.0,
									"id" : "obj-6",
									"linecount" : 2,
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 141.0, 87.0, 452.0, 40.0 ],
									"text" : "creating faustgen~ object without a specific <name_argument> \nlet's you define it only for this instance with a default name factory ID"
								}

							}
, 							{
								"box" : 								{
									"bitcode" : "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",
									"bitcode_size" : 8344,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"id" : "obj-1",
									"maxclass" : "newobj",
									"numinlets" : 2,
									"numoutlets" : 2,
									"outlettype" : [ "signal", "signal" ],
									"patching_rect" : [ 9.0, 96.5, 100.0, 21.0 ],
									"serial_number" : "C02JV2K0DKQ464 bits",
									"sourcecode" : "import(\"stdfaust.lib\"); \n \nprocess = _,_;",
									"sourcecode_size" : 176,
									"text" : "faustgen~",
									"varname" : "faustgen-fc51180",
									"version" : "1.12"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 44.382671,
									"frgb" : 0.0,
									"id" : "obj-16",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 7.0, 5.0, 205.0, 56.0 ],
									"text" : "faustgen~"
								}

							}
, 							{
								"box" : 								{
									"fontname" : "Arial",
									"fontsize" : 12.0,
									"frgb" : 0.0,
									"id" : "obj-14",
									"maxclass" : "comment",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 7.0, 61.0, 250.0, 20.0 ],
									"text" : "Faust as a Max/MSP external : version 1.12"
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-49",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 118.5, 253.5, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "4",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-93",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 118.5, 97.0, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "1",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-15",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 116.5, 429.0, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "6",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-37",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 116.5, 738.5, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "9",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-46",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 116.5, 692.5, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "8",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-12",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 116.5, 364.0, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "5",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-43",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 116.5, 654.0, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "7",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-8",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 118.5, 210.5, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "3",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
, 							{
								"box" : 								{
									"background" : 1,
									"bgcolor" : [ 1.0, 0.788235, 0.470588, 1.0 ],
									"border" : 0,
									"bordercolor" : [ 0.0, 0.0, 0.0, 1.0 ],
									"fontface" : 1,
									"fontname" : "Arial",
									"fontsize" : 13.0,
									"hint" : "",
									"id" : "obj-3",
									"ignoreclick" : 1,
									"maxclass" : "textbutton",
									"numinlets" : 1,
									"numoutlets" : 3,
									"outlettype" : [ "", "", "int" ],
									"parameter_enable" : 0,
									"patching_rect" : [ 118.5, 156.5, 20.0, 20.0 ],
									"rounded" : 60.0,
									"text" : "2",
									"textcolor" : [ 0.34902, 0.34902, 0.34902, 1.0 ],
									"textovercolor" : [ 0.2, 0.2, 0.2, 1.0 ]
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-17", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-10", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-10", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-18", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-18", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-19", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-26", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-29", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-26", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"midpoints" : [ 16.5, 495.25, 16.5, 495.25 ],
									"source" : [ "obj-30", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-26", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-34", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-26", 0 ],
									"disabled" : 0,
									"hidden" : 0,
									"source" : [ "obj-36", 0 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 10.0, 51.0, 50.0, 20.0 ],
					"saved_object_attributes" : 					{
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"default_fontsize" : 13.0,
						"description" : "",
						"digest" : "",
						"fontface" : 0,
						"fontname" : "Arial",
						"fontsize" : 13.0,
						"globalpatchername" : "",
						"tags" : ""
					}
,
					"text" : "p basic",
					"varname" : "basic_tab"
				}

			}
 ],
		"lines" : [  ],
		"parameters" : 		{
			"obj-6::obj-38" : [ "live.gain~[5]", "live.gain~", 0 ],
			"obj-8::obj-38" : [ "live.gain~[9]", "live.gain~", 0 ],
			"obj-5::obj-38" : [ "live.gain~[4]", "live.gain~", 0 ]
		}
,
		"dependency_cache" : [ 			{
				"name" : "faustgen~.mxo",
				"type" : "iLaX"
			}
 ]
	}

}

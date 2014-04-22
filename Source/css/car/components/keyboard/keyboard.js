/* Copyright (C) Jaguar Land Rover - All Rights Reserved
 *
 * Proprietary and confidential
 * Unauthorized copying of this file, via any medium, is strictly prohibited
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY 
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * Filename:		 header.txt
 * Version:              1.0
 * Date:                 January 2013
 * Project:              Widget incorporation
 * Contributors:         XXXXXXX
 *                       xxxxxxx
 *
 * Incoming Code:        GStreamer 0.93, <link>
 *
*/

var Keyboard=function()
    {
        this.keyboard=$("<div class='keyboard'></div>");
        this.shifted=false;
        this.single_shift=false;
        this.symbols=false;
        this.focus=null;
        this.selectionStart=0;
        this.selectionEnd=0;
        $("body").append(this.keyboard);
        var alphabet={
            characters: "qwertyuiopasdfghjklzxcvbnm".split(""),
            shifted: "QWERTYUIOPASDFGHJKLZXCVBNM".split(""),
            symbols:"1234567890@%*+-'\"(),.?!/:_{}|<>".split("")
        };
        for(var i=0;i<10;i++)
            {
                this.addKey(alphabet.characters[i], alphabet.shifted[i], alphabet.symbols[i], i*9.5+1, 76);
            }
        for(var i=10;i<19;i++)
            {
                this.addKey(alphabet.characters[i], alphabet.shifted[i], alphabet.symbols[i], (i-10)*9.5+5.8, 51);
            }
        
        for(var i=20;i<26;i++)
            {
                this.addKey(alphabet.characters[i], alphabet.shifted[i], alphabet.symbols[i], (i-20)*9.5+15.9, 26);
            }
        var self=this;
        
        this.addSpecialTypedKey("", 18, 2, function(){ return " "; }).addClass("key_special_spacebar");
		
        this.addSpecialTypedKey("", 77, 2, function(){ return "\n"; }).addClass("key_special_return");
        
        this.addSpecialKey("", "<div class='key_shift'></div><div class='key_shift_on'></div>", "", 1, 27, function(){ self.toggle_shift(); }).addClass("key_special_capslock");
        this.addSpecialKey("<div class='key_special_symlock_off'></div>", "<div class='key_special_symlock_off'></div>", "<div class='key_special_symlock_on'></div>", 1, 2, function(){ self.toggle_symbols(); }).addClass("key_special_symlock");
        this.addSpecialKey("", "", "", 77, 27, function(){ self.backspace(); }).addClass("key_special_bksp");

        //$("input[type=text], input[type=password], textarea").focus(function(event){ console.log(event); self.focus=$(this); self.open(true); });
        $("html").on("focusin", Keyboard.focus_elements, function(event){ console.log(event); self.focus=$(this); self.open(true); });
        $("html").on("click", function(event){ var target=$(event.target); if( target.parents(".keyboard").length==0 && !target.hasClass("keyboard") && !target.is(Keyboard.focus_elements) ){ self.open(false); } });
    }

Keyboard.focus_elements="input[type=text], input[type=password], input[type=number], input[type=email], input[type=url], textarea";

Keyboard.prototype.open=function(open)
    {
        if(open)
            {
                this.keyboard.show();
            }
        else
            {
                this.keyboard.hide();
            }
    }

Keyboard.prototype.addKey=function(character, shifted, symbol, x, y)
    {
        var button=$("<div class='key_button' style='left:"+x+"%; bottom:"+y+"%;'></div>");
        button.append($("<div class='key_character'><span class='key_big_character'>"+character+"</span><span class='key_small_character'>"+symbol+"</span></div>"));
        button.append($("<div class='key_shifted'><span class='key_big_character'>"+shifted+"</span><span class='key_small_character'>"+character+"</span></div>"));
        button.append($("<div class='key_symbol'><span class='key_big_character'>"+symbol+"</span><span class='key_small_character'>"+character+"</span></div>"));
        var self=this;
        button.click(
            function(){ self.action(
                function(){ return self.type(character, shifted, symbol); }
                );
            });
        this.keyboard.append(button);
        return button;
    }

Keyboard.prototype.addSpecialKey=function(character, shifted, symbol, x, y, callback)
    {
        var button=$("<div class='key_button' style='left:"+x+"%; bottom:"+y+"%;'></div>");
        button.append($("<div class='key_character'>"+character+"</div>"));
        button.append($("<div class='key_shifted'>"+shifted+"</div>"));
        button.append($("<div class='key_symbol'>"+symbol+"</div>"));
        var self=this;
        button.click( callback );
        this.keyboard.append(button);
        return button;
    }

Keyboard.prototype.addSpecialTypedKey=function(character, x, y, callback)
    {
        var button=$("<div class='key_button' style='left:"+x+"%; bottom:"+y+"%;'></div>");
        button.append($("<div class='key_special_character'>"+character+"</div>"));
        var self=this;
        button.click(function(){ self.action(callback); });
        this.keyboard.append(button);
        return button;
    }

Keyboard.prototype.action=function(callback)
    {
        var value=this.focus.val();
        if(false){ //this.focus[0].selectionStart){
	        var prefix=value.slice(0, this.focus[0].selectionStart);
	        var suffix=value.slice(this.focus[0].selectionEnd, value.length);
	        var select=this.focus[0].selectionStart+1;
	        this.focus.val((prefix || "")+callback()+(suffix || ""));
        	this.focus.focus();
        	this.focus[0].selectionEnd = this.focus[0].selectionStart = select;
    		}
        else
        	{
            this.focus.val(value+callback());
            var select=this.focus.val().length;
            this.focus.focus();
        	}
        if(this.single_shift)
            {
                this.single_shift=false;
                this.toggle_shift();
            }
    }

Keyboard.prototype.backspace=function(callback)
    {
        var value=this.focus.val();
        if(false){ //this.focus[0].selectionStart){
	        if(this.focus[0].selectionEnd == this.focus[0].selectionStart)
	            {
	                this.focus[0].selectionStart--;
	            }
	        var prefix=value.slice(0, this.focus[0].selectionStart);
	        var suffix=value.slice(this.focus[0].selectionEnd, value.length);
	        var select=this.focus[0].selectionStart;
	        this.focus.val((prefix || "")+(suffix || ""));
	        this.focus.focus();
	        this.focus[0].selectionEnd = this.focus[0].selectionStart = select;
        }else{
            var prefix=value.slice(0, value.length-1);
            var select=0;
            this.focus.val((prefix || ""));
            this.focus.focus();
        }
    }

Keyboard.prototype.toggle_shift=function()
    {
        if(this.single_shift)
            {
            this.single_shift=false;
            }
        else
            {
                this.symbols=false;
                $(".key_symbol").hide();
                this.shifted=!this.shifted;
                $(".key_character").toggle(!this.shifted);
                this.single_shift=this.shifted;
            }
        $(".key_shifted").toggle(this.shifted);
        $(".key_shift").toggle(this.shifted && this.single_shift);
        $(".key_shift_off").toggle(this.shifted && !this.single_shift);
    }

Keyboard.prototype.toggle_symbols=function()
    {
        this.shifted=false;
        this.single_shift=false;
        $(".key_shifted").hide();
        this.symbols=!this.symbols;
        $(".key_character").toggle(!this.symbols);
        $(".key_symbol").toggle(this.symbols);
    }

Keyboard.prototype.type=function(character, shifted, symbol)
    {
        if(this.shifted)
            {
            return shifted
            }
        else if(this.symbols)
            {
            return symbol;
            }
        return character;
    }

var my_keyboard;

window.onload=function(){ my_keyboard=new Keyboard(); }
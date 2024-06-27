
document.querySelector('[name="file"]').onchange = function(){
	if(this.files[0]){
		let name = this.files[0].name ;
	document.querySelector('.file_name').innerHTML = name ;
	console.log(name) ;
	}
	
};


window.addEventListener('load', function() {
	
	setTimeout(function(){
		
			document.querySelector('.logo').style.opacity = 1;

	}, 500);
	setTimeout(function(){
		
			document.querySelector('.one').style.opacity = 1;

	}, 1500);
	
	setTimeout(function(){
		
			document.querySelector('.two').style.opacity = 1;

	}, 2500);
	setTimeout(function(){
		document.querySelector('.form').style.opacity = 1;
            document.querySelector('.logout').style.opacity = 1;
			

	}, 3500);
    console.log('All assets are loaded')
})
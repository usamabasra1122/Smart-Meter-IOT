
  
 
    // Your web app's Firebase configuration
    var firebaseConfig = {
      apiKey: "AIzaSyBKKBopXKJW8oIKbyZtWbvjWP5OP3FR_xk",
      authDomain: "smart-meter-c862d.firebaseapp.com",
      databaseURL: "https://smart-meter-c862d.firebaseio.com",
      projectId: "smart-meter-c862d",
      storageBucket: "smart-meter-c862d.appspot.com",
      messagingSenderId: "474486730299",
      appId: "1:474486730299:web:63c9d8374d951c6f4cf61e",
      measurementId: "G-5776EGZEXD"
    };
    // Initialize Firebase
    var app = firebase.initializeApp(firebaseConfig);
    firebase.analytics();

    
    auth = firebase.auth();
    var db = firebase.firestore();


    

console.log("Common");

 jQuery.expr[':'].contains = function(a, i, m) {
  return jQuery(a).text().toUpperCase()
      .indexOf(m[3].toUpperCase()) >= 0;
};


function trigger_click(input){
  $(input).trigger("click");
}

function confirmation( Message, func ) {
  $('#confirmation').modal('show');
  $("#confirmation-message").text(Message);
  $("#confirmation-yes").off('click').on('click', func);
}


function ShowLoading(Message){
    $(".messageLoading").text(Message);
    $(".loading-screen").removeClass("hide");
}

function DismissLoading(){
    $(".loading-screen").addClass("hide");
}   

function SnackBar(Message) {
    var x = document.getElementById("snackbar");
    x.innerHTML = Message;
    x.className = "show";
    setTimeout(function(){ x.className = x.className.replace("show", ""); }, 3000);
}

// form submissions
 $('form[name="forgot-password"]').submit(function(event){
        event.preventDefault();
        email = $('#reset-email').val();
        ShowLoading("Sending mail");
        auth.sendPasswordResetEmail(email)
                .then(user => {
                    DismissLoading();
                    SnackBar("Please check your inbox.");
                    trigger_click(".close");
                })
                .catch(e => {
                    DismissLoading();
                    SnackBar(e.message);
                });
    });



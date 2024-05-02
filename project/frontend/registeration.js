document.getElementById("registrationForm").addEventListener("submit", function(event) {
    event.preventDefault();
    var email = document.getElementById("email").value;

    if (!email.endsWith("@nitt.edu")) {
        alert("Please use your college email address.");
        return;
    }

    this.submit();
});

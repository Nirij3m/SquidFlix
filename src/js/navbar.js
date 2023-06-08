document.getElementById("navbar-menu").addEventListener("click", function() {
    var navbar_center = document.querySelector("div.navbar-center");
    var navbar_right = document.querySelector("div.navbar-right");
    navbar_center.classList.toggle("hidden");
    navbar_right.classList.toggle("hidden");
});

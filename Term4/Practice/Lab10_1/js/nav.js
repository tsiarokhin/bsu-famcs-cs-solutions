
document.querySelectorAll(".nav-link").forEach(function(e) {
    e.addEventListener("pointerenter", function(event) {
        var targetElement = event.target || event.srcElement;
        targetElement.style.backgroundColor = "green"; 
    });
    e.addEventListener("pointerleave", function(event) {
        var targetElement = event.target || event.srcElement;
        targetElement.style.backgroundColor = "red"; 
    });
});
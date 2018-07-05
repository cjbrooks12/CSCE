function toggle_visibility(id) {
    var e = document.getElementById(id);
    var button = document.getElementById("toggle_button");
    if(e.style.display == 'block') {
        e.style.display = 'none';
        button.value = "Show Original";
    }
    else {
        e.style.display = 'block'
        button.value = "Hide Original";
    }
}
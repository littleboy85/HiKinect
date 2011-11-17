function Kinect(id, element, config) {
    this.id = id;
    this.element = $(element);
    this.element.hide();
    this.config = config;
    this.container = $('<div id="kinect_setup_container"></div>');
    this.element.before(this.container)
    this.container.append('<div id="kinect_message"></div>');
    this.h_rate = this.config.human_height/1600.0;
    this.w_rate = this.config.human_width/1600.0;
}

Kinect.prototype.init = function(onStart, onMove) {
    this.kinect = document.getElementById(this.id);
    if (!this.kinect || !this.kinect.init) return false;
    var this_ = this;
    this.onStart = onStart;
    this.onMove = onMove;
    this.kinect.init(function(msg, status, error){
        console.log(msg);
        this_.onMsg(msg, status, error);
    });
    return true;
}

Kinect.prototype.bonusRate = function(){
  return this.version === 'kinect' ? 2 : 1;
}

Kinect.prototype.onMsg = function(msg, status, error) {
    var message = $('#kinect_message');
    switch (msg) {
        case "CONTEXT_INIT":
            message.text('Hello, please wait for kinect connected !');
        break;
        case "USERGENERATOR_CREATE":
            if (status === "65565") {
              message.text('Can not find any kinect device, game will start with mouse in 3 second');
              this.element.mousemove(this, function(e){
                var x, y;
                if (!e.offsetX || !e.offsetY){
                  x = e.layerX - $(this).position().left;
                  y = e.layerY - $(this).position().top;
                }else{
                  x = e.offsetX;
                  y = e.offsetY;
                }
                e.data.onMove(x, y);
              });
              setTimeout(function(this_){
                this_.container.css('background', 'transparent');
                this_.container.remove()
                this_.element.show();
                this_.onStart();
              }, 3000, this);
            }else{
              this.element.unbind('mousemove');
              message.text('Please stand in front of kinect, at lease 1 m');
              var canvas = $('<canvas id="kinectSetup" width="'+
                  this.config.width+'" height="'+this.config.height+'"></canvas>');
              this.container.css('background', 'transparent');
              this.container.append(canvas);
              this.context = canvas[0].getContext("2d");
              this.version = 'kinect';
            }
        break;
        case "START_GENERATING":
        break;
        case "NEW_USER":
            message.text('Please follow our lead !');
            var human_width = this.config.human_width;
            var human_height = this.config.human_height;
            this.pos_helper = {
                XN_SKEL_HEAD: {x: 0, y: 400},
                XN_SKEL_NECK: {x: 0, y: 200},
                XN_SKEL_LEFT_SHOULDER: {x: -200, y: 200},
                XN_SKEL_LEFT_ELBOW: {x: -400, y: 160},
                XN_SKEL_LEFT_HAND: {x: -400, y: 400},
                XN_SKEL_RIGHT_SHOULDER: {x: 200, y: 200},
                XN_SKEL_RIGHT_ELBOW: {x: 400, y: 160},
                XN_SKEL_RIGHT_HAND: {x: 400, y: 400},
                XN_SKEL_TORSO: {x: 0, y: -100},
                XN_SKEL_LEFT_HIP: {x: -200, y: -200},
                XN_SKEL_LEFT_KNEE: {x: -200, y: -500},
                XN_SKEL_LEFT_FOOT: {x: -200, y: -700},
                XN_SKEL_RIGHT_HIP: {x: 200, y: -200},
                XN_SKEL_RIGHT_KNEE: {x: 200, y: -500},
                XN_SKEL_RIGHT_FOOT: {x: 200, y: -700}
            };
            this.generate_helper(this);
        break;
        case "POSE_DETECTED":
        break;
        case "START_CALIBRATION":
            message.text('Stay this pos for 3 second !');
        break;
        case "CALIBRATION_SUCCESS": 
            message.text('Great job, game will start in 3 second');
            delete this.pos_helper;
            
        break;
        case "CALIBRATION_FAIL":
        break;
    }
}

Kinect.prototype.update = function(this_){
  var sk = this_.kinect.getSkeleton();
    var coor = this_.getXY(sk['XN_SKEL_TORSO']);

  this_.onMove(sk);
  setTimeout(this_.update, 10, this_);
}

Kinect.prototype.getXY = function(joint){
    var x = joint.x;
    var y = joint.y;
    x = this.config.start_x-x*this.w_rate;
    y = this.config.start_y-y*this.h_rate;
    return {x: x, y: y};
}

Kinect.prototype.moveTo = function(joint){
    var xy = this.getXY(joint);
    this.context.moveTo(xy.x, xy.y);
}

Kinect.prototype.lineTo = function(joint){
    var xy = this.getXY(joint);
    this.context.lineTo(xy.x, xy.y);
}

Kinect.prototype.drawSkeleton = function(sk, clean) {
    if (clean){
        this.context.clearRect(0, 0, this.config.width, this.config.height);
    }
    this.context.beginPath();
    this.moveTo(sk['XN_SKEL_HEAD']);
    this.lineTo(sk['XN_SKEL_NECK']);
    this.lineTo(sk['XN_SKEL_LEFT_SHOULDER']);
    this.lineTo(sk['XN_SKEL_LEFT_ELBOW']);
    this.lineTo(sk['XN_SKEL_LEFT_HAND']);
    this.moveTo(sk['XN_SKEL_NECK']);
    this.lineTo(sk['XN_SKEL_RIGHT_SHOULDER']);
    this.lineTo(sk['XN_SKEL_RIGHT_ELBOW']);
    this.lineTo(sk['XN_SKEL_RIGHT_HAND']);
    this.moveTo(sk['XN_SKEL_NECK']);
    this.lineTo(sk['XN_SKEL_TORSO']);
    this.lineTo(sk['XN_SKEL_LEFT_HIP']);
    this.lineTo(sk['XN_SKEL_LEFT_KNEE']);
    this.lineTo(sk['XN_SKEL_LEFT_FOOT']);
    this.moveTo(sk['XN_SKEL_TORSO']);
    this.lineTo(sk['XN_SKEL_RIGHT_HIP']);
    this.lineTo(sk['XN_SKEL_RIGHT_KNEE']);
    this.lineTo(sk['XN_SKEL_RIGHT_FOOT']);
    this.context.stroke();
}

Kinect.prototype.generate_helper= function (this_){
    if (this_.quit_helper) return;
    if (this_.pos_helper) {
        this_.drawSkeleton(this_.pos_helper, true);
        this_.drawSkeleton(this_.kinect.getSkeleton(), false);
    }else{
        this_.drawSkeleton(this_.kinect.getSkeleton(), true);
    }
    setTimeout(this_.generate_helper, 10, this_);
}


function drawGeometry
    
    [e,g] = readGeometryFile('BowTie.txt');
    draw(e,g);
    title('Original Bow Tie Geometry');
    [e,g] = readGeometryFile('BowTie.out');
    draw(e,g);
    title('Discretized Bow Tie Geometry');
    
    [e,g] = readGeometryFile('RoundedRectangle.txt');
    draw(e,g);
    title('Original Rounded Rectangle Geometry');
    [e,g] = readGeometryFile('RoundedRectangle.out');
    draw(e,g);
    title('Discretized Rounded Rectangle Geometry');
    
    
end


function [edges, geometry] = readGeometryFile(fileName)

    % my sample text contains ---> apple, baseball, car, donut, & elephant in single column.
    fp = fopen(fileName);
    
    edges = [];
    geometry = [];
    while(~feof(fp))
        thisLine = fgets(fp);
        [e,g] = parseInput(thisLine);
        edges = [edges;e];
        geometry = [geometry;g];
    end
    geometry = cell2mat(geometry);
        
    fclose(fp);
end

function [e,g] = parseInput( line )

    subStrs = split(line,[" ", "->", "\r"]);
    g = subStrs(1);
    coord1 = split(subStrs{2},["(",",",")"]);
    e(1) = str2double(coord1(2));
    e(2) = str2double(coord1(3));
    
    coord2 = split(subStrs(5),["(",",",")"]);
    e(3) = str2double(coord2(2));
    e(4) = str2double(coord2(3));
end

function drawArrow( p1, p2 )
    dp = p2-p1;                         % Difference
    hold on;
    quiver(p1(1),p1(2),dp(1),dp(2),0,'color',[0 0 1])
    % grid
    % axis([-10  10   -10  10])
    % text(p1(1),p1(2), sprintf('(%.0f,%.0f)',p1))
    % text(p2(1),p2(2), sprintf('(%.0f,%.0f)',p2))
    hold off;
end


function r = getRadius( p1, p2 )
    r = norm(p2 - p1) / sqrt(2);
end

function XY = getCenterOfQuadrant( p1, p2 )
    x1 = p1(1);
    y1 = p1(2);
    x2 = p2(1);
    y2 = p2(2);
    
    p3_1 = [x1 y2];
    v1 = [p2 - p1 0];
    v3_1 = [p3_1 - p2 0];
    
    p3_2 = [x2 y1];
    v3_2 = [p3_2 - p2 0];
    
    kVec_1 = cross(v1,v3_1);
    kVec_2 = cross(v1,v3_2);
    
    s1 = sign(kVec_1(3));
    s2 = sign(kVec_2(3));
    
    if( s1 <= 0 )
        x = x2;
        y = y1;
    else
        x = x1;
        y = y2;
    end
    
    XY = [x y];
end

function drawArc( p1, p2, center, r )
    
    dv1 = p1 - center;
    dv2 = p2 - center;
    
    theta1 = atan2(dv1(2),dv1(1));
    theta2 = atan2(dv2(2),dv2(1));
    if( theta2 < 0 )
        theta2 = theta2 + 2*pi;
    end
    rad2deg(theta1)
    rad2deg(theta2)
    nPoints = 1000;
    dtheta = (theta2 - theta1)/nPoints;
    theta = theta1:dtheta:theta2;
    x = center(1) + r.*cos(theta);
    y = center(2) + r.*sin(theta);
    plot(x,y,'r');
end

function drawLineSegments( points )
    hold on;
        nPoints = size(points,1);
        for i = 1 : nPoints
            p1 = points(i,1:2);
            p2 = points(i,3:4);
            drawArrow(p1,p2);
        end
    hold off;
end


function drawQuadrants( quadrantPoints )
    hold on;
        nPoints = size(quadrantPoints,1);
        for i = 1 : nPoints
            p1 = quadrantPoints(i,1:2);
            p2 = quadrantPoints(i,3:4);
            c = getCenterOfQuadrant(p1,p2);
            r = getRadius(p1,p2);
            scatter(c(1),c(2),'xr');
            drawArc(p1,p2,c,r);

        end
    hold off;
end

function draw( e , g )
    figure;
    lines = e( g == 'L', :);
    quadrants = e( g == 'C', :);
    drawLineSegments(lines);
    drawQuadrants(quadrants);
end

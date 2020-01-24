function J = cost_function(X, y, theta)
   m = length(y); % number of training examples
   J = 0;
   r=0;
   for i=1:m,
      h=(theta(1) + (theta(2)*X(i,2)));
      d=h-y(i);
      r=r+(d*d);
   end;
   J=(r/(2*m));

end

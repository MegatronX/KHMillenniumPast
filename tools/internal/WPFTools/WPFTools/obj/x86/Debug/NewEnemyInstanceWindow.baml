   M S B A M L   `   `   `  ����  WPFTools%    WPFTools.NewEnemyInstanceWindow   5   	   W SPresentationCore, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35\ XPresentationFramework, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35U QWPFToolkit, Version=3.5.40128.1, Culture=neutral, PublicKeyToken=31bf3856ad364e35^ ZWindowsFormsIntegration, Version=3.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35H 9http://schemas.microsoft.com/winfx/2006/xaml/presentation      5      8x,http://schemas.microsoft.com/winfx/2006/xaml    5      -   5        $��AddNewEnemyInstanceWindow��5   V     � Title$  NewEnemyInstanceWindow��6   $	��309��6$   $	��687��61   .��5      �  � DataContext 5   
   �� 5       �� ElementName$ AddNewEnemyInstanceWindow��6    �� Path$ NewEnemyInstanceElement�6>   .+�5	   
   �� -   5        $��RootEnemyNameLabel��5	   l   $��28��6   $
��Left=�6?   $��5,30,0,0q�6Z   $	��Top=�6�   $	��245��6�   $��16(�6�   ��6   ��  �� XPath$ ../@name��6�   �� 5
   
   -   5        $��label2��5
   I   $��28��6   $
��Left=�6   $��6,74,0,0q�67   $	��Top=�6W   $��41��6o   .��6z   Level:6�   �� 5   
   -   5        $��CancelButton��5   >   $��Right=�6   $��0,0,8,8q�6-   $��75��6R   $��23��6]   $��Bottom=�6i   .��6�   Cancel6�   �� 5   
   -   5        $��EnemyLevelBox��5   j   $��23��60   $
��Left=�6<   $��	53,77,0,0q�6W   $	��Top=�6   $��48��6�   ��6   �� $ @level��6�   �� 5   
   -   5        $��label5��5   n   
����=H�$
��Bold"�6+   
�������$��28��6P   $��0,-1,0,0q�6\   $	��Top=�6|   .��6�   Add New Enemy Instance6�   �� 5   
   -   5        $��EnemyStatViewDisplay��5   _   $��	0,54,8,37q�6{   $��Right=�6�   $	��281��6�    6   �� $ Stats����67   �� $ 
Attributes� �� View 5      �� 5      .P�5      ��  �� Width$	 120��6%   $��	Stat Name��61    �� CellTemplate 5      �� 5      .R�5   "   � .+�5   &   �� $	��120��60   ��6<   �� *Name+5   #   5      5      �� 5      $	 130��6%   $��
Stat Value��61    5      �� 5      .R�5   "   � .+�5   &   �� $	��130��6.   ��6:   �� *Value+5    #   5!      5#      5$      5&      �� 5'   
   -   5        $��label1��5'   L   $��28��6   $��Right=�6   $��
0,26,169,0q�68   $	��Top=�6Z   $	��120��6r   .��6~   Stats6�   �� 5(   
   -	   5        $��label3��5(   @   $
��Left=�6   $��6,108,0,135q�6+   $	��120��6N   .��6Z   Description6g   �� 5)   
   -
   5        $��EnemyDescriptionBox��5)   j   $
��Left=�6<   $��	6,131,0,8q�6W   $	��244��6�   ��6   �� $ Description/@value��6�   �� 5*   
   -   5        $��SaveInstance��5*   K   $��23��6   $��Right=�6   $��0,0,89,8q�69   $��Bottom=�6_   $��75��6z   .��6�   Save6�   5+      5,      
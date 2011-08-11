// Our method which is called during initialization of the toolbar.
var NodeEmbed = function NodeEmbed( name )
{
  this.Name = name ;
  this.EditMode = FCK.EditMode;
}

// Disable button toggling.
NodeEmbed.prototype.GetState = function()
{
	return FCK_TRISTATE_OFF;
}

// Register the Drupal tag commands.
FCKCommands.RegisterCommand( 'NodeEmbed', new FCKDialogCommand( 'NodeEmbed', 'Node Embed', 
  '/fckeditor-node-embed', 800, 490 ) ) ;

// Create the Drupal tag buttons.
var oDrupalItem = new FCKToolbarButton( 'NodeEmbed', FCKLang.NodeEmbedTitle, FCKLang.NodeEmbedooltip, FCK_TOOLBARITEM_ICONTEXT, true, true ) ;
oDrupalItem.IconPath = FCKConfig.PluginsPath + 'NodeEmbed/nodeembed.gif';
FCKToolbarItems.RegisterItem( 'NodeEmbed', oDrupalItem ) ;

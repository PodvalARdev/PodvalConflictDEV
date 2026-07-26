[ComponentEditorProps(category: "GameMode Component", description: "Allows VIPs to use the Admin queue bypass, but strips their admin powers upon connection.")]
class VIPRoleRestrictorComponentClass : GameModeComponentClass {}

class VIPRoleRestrictorComponent : GameModeComponent
{
    // Hardcoded list of VIPs who should be demoted to normal players
    protected ref array<string> m_aVipGuids = {
        "28a51194-b5ab-40d4-8be6-ada0cfe9f98d"
    };

    override void OnPlayerConnected(int playerId)
    {
        super.OnPlayerConnected(playerId);

        PlayerManager playerManager = GetGame().GetPlayerManager();
        if (!playerManager)
            return;

        string playerGuid = playerManager.GetPlayerPlayerId(playerId);

        // Check if this connecting player is one of our VIPs
        if (m_aVipGuids.Contains(playerGuid))
        {
            // Instantly demote them to a standard player role, removing access to admin menus/tools
            playerManager.SetPlayerRole(playerId, EPlayerRole.NONE);
            
            Print(string.Format("[VIP Security] Stripped admin rights from VIP Player (ID: %1) after queue bypass.", playerId), LogKind_NORMAL);
        }
    }
}

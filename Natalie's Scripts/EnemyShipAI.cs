using System.Collections;
using UnityEngine;

public class EnemyShipAI : MonoBehaviour
{
/* All other code in this script is not written by me. This is the part of the code I have written in relation to the freezing cannonball */

    //freezing cannon affecting the reload speed
    public void slowReload(float decreaseValue, float decreaseDuration)
    {
        StartCoroutine(ReduceShotSpeed(decreaseValue, decreaseDuration));
    }
    IEnumerator ReduceShotSpeed(float value, float duration)
    {
        float originalSpeed = shootingCooldown;
        shootingCooldown += value;
        yield return new WaitForSecondsRealtime(duration);
        shootingCooldown = originalSpeed;
    }
}
